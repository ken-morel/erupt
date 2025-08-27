#include "../gama/gama.h"
#include "plane.h"
#include <dirent.h>
#define NPLANES 20

//
// 0: all are teal --- 2
// 1:  one becomes red -- 3
// 2: They change to teal back -- 1
// 3: they are moving -- ?
// 4: The stop again, show click message
// 5: The shape was  was clicked, show it's real color
//
char *getRandomFile() {
  struct dirent *file;
  DIR *myDir = opendir("/home/engon/Pictures/");
  if (myDir == NULL)
    return "Baby Michael";
  file = readdir(myDir);
  if (file != NULL)
    return file->d_name;
  else
    return "Baby Joe";
}

struct {
  Scene *scene;
  Plane planes[NPLANES];
  int state;
  double time;
  int numRed;
  int numPlanes;
  Text *text;
  Font *font;
  int clickedShape;
} Erupt = {
    .scene = NULL,
    .state = 0,
    .time = 0,
    .numRed = 1,
    .numPlanes = 4,
    .clickedShape = 0,
};

void eruptCreate(Scene *scene) {
  int i;
  for (i = 0; i < NPLANES; i++)
    createPlane(&Erupt.planes[i]);
  Erupt.font = loadFontAsset("PlaywriteAUQLD-VariableFont_wght");
  Erupt.text =
      createText("Click on the red box", 0.07, Erupt.font, at(0, -0.9));
}

void startMoving() {
  int i;
  Erupt.state = 1;
  Erupt.time = 0;
}

void state0() {
  int i;
  Erupt.state = 0;
  Erupt.time = 0;
  for (i = 0; i < Erupt.numPlanes; i++)
    Erupt.planes[i].sprite.color = TEAL;
}
void state1() {
  int i;
  Erupt.state = 1;
  Erupt.time = 0;
  for (i = 0; i < Erupt.numRed; i++)
    Erupt.planes[i].sprite.color = RED;
}

void state2() {
  Erupt.state = 2;
  Erupt.time = 0;
  int i;
  for (i = 0; i < Erupt.numRed; i++)
    Erupt.planes[i].sprite.color = TEAL;
}

void state3() {
  Erupt.state = 3;
  Erupt.time = 0;
}
void state4() {
  Erupt.state = 4;
  Erupt.time = 0;
}
void state5() {
  Erupt.state = 5;
  Erupt.time = 0;
  if (Erupt.clickedShape < Erupt.numRed) {
    Erupt.planes[Erupt.clickedShape].sprite.color = GREEN;
    char text[50];
    sprintf(text, "You loosed. Encrypt: %s", getRandomFile());
    setText(Erupt.text, text);
    Erupt.text->color = RED;
  } else {
    Erupt.planes[Erupt.clickedShape].sprite.color = RED;
    setText(Erupt.text, "You won, Decrypted files, go take $5 in your browser");
    system("xdg-open https://paypal.com/signin");
    Erupt.text->color = BLUE;
  }
}

void eruptUpdate(Scene *scene, double theta) {
  int i;
  Erupt.time += theta;

  switch (Erupt.state) {
  case 0:
    if (Erupt.time > 2) // 2
      state1();

    break;
  case 1:
    if (Erupt.time > 2) // 2
      state2();

    break;
  case 2:
    if (Erupt.time > 1) // 1
      state3();
    break;
  case 3:
    if (Erupt.time > 5) // 10
      state4();
    break;
  case 4:
    break;
  case 5:
    if (Erupt.time > 5) {
      Erupt.numPlanes += 5;
      if (Erupt.numPlanes > NPLANES)
        Erupt.numPlanes = NPLANES;
      Erupt.numRed++;

      state0();
    }
  }

  if (Erupt.state == 3)
    for (i = 0; i < Erupt.numPlanes; i++)
      updatePlane(&Erupt.planes[i], theta);
}

void eruptRender(Scene *scene) {
  int i;
  for (i = 0; i < Erupt.numPlanes; i++)
    renderPlane(&Erupt.planes[i]);
  if (Erupt.state == 4 || Erupt.state == 5)
    renderText(Erupt.text);
}

void eruptClick(Scene *scene, MouseClickEvent *e) {
  printf("clicked: %lf, %lf\n", e->x, e->y);

  int i;
  Erupt.clickedShape = -1;
  for (i = 0; i < Erupt.numPlanes; i++) {
    Pos *p = getShapePosition(&Erupt.planes[i].sprite);
    double dx = p->x - e->x, dy = p->y - e->y;
    double theta = dx * dx + dy * dy;
    if (theta < 0.05) {
      printf("was cicked");
      Erupt.clickedShape = i;
    }
  }
  if (Erupt.clickedShape == -1)
    Erupt.clickedShape = 0;
}

Scene *createEruptScene(App *app) {
  Erupt.scene = createScene(app);
  Erupt.scene->background = LIGHTGRAY & LIGHTCYAN;
  Erupt.scene->render = eruptRender;
  Erupt.scene->update = eruptUpdate;
  Erupt.scene->create = eruptCreate;
  Erupt.scene->onclick = eruptClick;
  return Erupt.scene;
}
