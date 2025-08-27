#include "../gama/gama.h"

#include "./erupt.h"
#include "./welcome.h"

// Initialize the applicaiton here
void init(App *app) {
  setAppSize(app, 700, 700);
  srand(clock());
}

// Create scenes, shapes, and bind them to the app
void create(App *app) { showScene(app, createWelcomeScene(app)); }

// When app closes
void shutdown(App *app) {}
