#include "../gama/gama.h"
#include "math.h"
#include <GL/gl.h>

typedef struct {
  Shape sprite;
  double direction;
} Plane;

struct {
  double speed;
} Planes = {
    .speed = 5,
};
int randRange(int n, int x) { return rand() % (x - n + 1) + n; }

void createPlane(Plane *p) {
  double px = (double)randRange(-100, 100) / 100.0;
  double py = (double)randRange(-100, 100) / 100.0;
  createRectangle(&p->sprite, at(px, py), at(0.15, 0.15), TEAL);
  p->direction = (double)randRange(0, 360);
  double vx = Planes.speed * sin(p->direction);
  double vy = Planes.speed * cos(p->direction);
  setShapeVelocity(&p->sprite, at(vx, vy));
  p->sprite.rotation->rot->z = p->direction * 500;
  setShapeRotation(&p->sprite, rotate(p->direction));
}

void updatePlane(Plane *p, double theta) {
  int i;
  updateShape(&p->sprite, theta);
  if (p->sprite.pos->pos->x > 0.9 || p->sprite.pos->pos->x < -0.9)
    p->sprite.pos->vel->x *= -1;
  if (p->sprite.pos->pos->y > 0.9 || p->sprite.pos->pos->y < -0.9)
    p->sprite.pos->vel->y *= -1;
}

void renderPlane(Plane *p) { renderShape(&p->sprite); }
