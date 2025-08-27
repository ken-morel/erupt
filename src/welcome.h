#include "../gama/gama.h"
#include "defs.h"

struct {
  Scene *scene;
  Font *font;
  Text *text;
  Sprite *img;
} Welcome = {
    .scene = NULL,
    .font = NULL,
    .text = NULL,
    .img = NULL,
};

void welcomeKey(Scene *s, KeyEvent *e) {
  showScene(s->app, createEruptScene(s->app));
}

void welcomeCreate(Scene *s) {
  Welcome.font = loadFontAsset("PlaywriteAUQLD-VariableFont_wght");
  Welcome.text =
      createText("Press any key to start", 0.2, Welcome.font, at(0, -0));
  Welcome.text->color = PURPLE;
  Welcome.img =
      createSprite("assets/images/home.png", 1000, 1000, at(-2, -2), at(2, 2));
}
void welcomeRender(Scene *s) {
  renderSprite(Welcome.img);
  // renderText(Welcome.text);
}

Scene *createWelcomeScene(App *app) {
  if (Welcome.scene == NULL) {
    Welcome.scene = createScene(app);
    Welcome.scene->background = WHITE;
    Welcome.scene->render = welcomeRender;
    Welcome.scene->create = welcomeCreate;
    Welcome.scene->onkey = welcomeKey;
    Welcome.scene->background = GRAY;
  }
  return Welcome.scene;
}
