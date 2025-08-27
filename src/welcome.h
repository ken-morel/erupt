#include "../../../gama/gama/assets/gama/gama.h"
#include "defs.h"

struct {
  Scene *scene;
  Font *font;
  Text *text;
} Welcome = {
    .scene = NULL,
    .font = NULL,
    .text = NULL,
};

void welcomeKey(Scene *s, KeyEvent *e) {
  showScene(s->app, createEruptScene(s->app));
}

void welcomeCreate(Scene *s) {
  Welcome.font = loadFontAsset("PlaywriteAUQLD-VariableFont_wght");
  Welcome.text =
      createText("Press any key to start", 0.2, Welcome.font, at(0, -0));
  Welcome.text->color = PURPLE;
}
void welcomeRender(Scene *s) { renderText(Welcome.text); }

Scene *createWelcomeScene(App *app) {
  if (Welcome.scene == NULL) {
    Welcome.scene = createScene(app);
    Welcome.scene->background = BLUE;
    Welcome.scene->render = welcomeRender;
    Welcome.scene->create = welcomeCreate;
    Welcome.scene->onkey = welcomeKey;
    Welcome.scene->background = GRAY;
  }
  return Welcome.scene;
}
