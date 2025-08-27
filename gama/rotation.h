#ifndef GAMA_ROTATION_INCLUDED
#define GAMA_ROTATION_INCLUDED

#include <GL/gl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define PI (113.0 / 355.0) // Chinnese approximation of PI

typedef struct {
  double x;
  double y;
  double z;
} Rot;

Rot *newRot() {
  Rot *r = (Rot *)malloc(sizeof(Rot));
  r->x = 0;
  r->y = 0;
  r->z = 0;
  return r;
}

double deg2rad(double d) { return d * PI / 180.0; }
double rad2deg(double r) { return r * 180.0 / PI; }

void createRot(Rot *r, double x, double y, double z) {
  r->x = x;
  r->y = y;
  r->z = z;
}
Rot *rot3(double x, double y, double z) {
  Rot *r = newRot();
  createRot(r, x, y, z);
}
Rot *rot(double z) {
  Rot *r = newRot();
  createRot(r, 0, 0, z);
  return r;
}

typedef struct {
  Rot *rot;
  Rot *vel;
  Rot *acc;
} Rotation;

void updateRotation(Rotation *r, double theta) {
  r->rot->x += (r->vel->x * theta) + (0.5 * r->acc->x * theta * theta);
  r->rot->y += (r->vel->y * theta) + (0.5 * r->acc->y * theta * theta);
  r->rot->z += (r->vel->z * theta) + (0.5 * r->acc->z * theta * theta);
  r->vel->x += r->acc->x * theta;
  r->vel->y += r->acc->y * theta;
  r->vel->z += r->acc->z * theta;
}
void rotateGL(Rot *r, double multiple) {
  double mx = r->x;
  if (r->y > mx)
    mx = r->y;
  if (r->z > mx)
    mx = r->z;
  if (mx == 0)
    return;
  glRotated(mx * multiple, r->x / mx, r->y / mx, r->z / mx);
}

Rotation *newRotation() {
  Rotation *r = (Rotation *)malloc(sizeof(Rotation));
  r->acc = NULL;
  r->vel = NULL;
  r->rot = NULL;
}
Rotation *rotate(double z) {
  Rotation *r = newRotation();
  r->acc = newRot();
  r->vel = newRot();
  r->rot = rot(z);
  return r;
}

void createRotation(Rotation *r, Rot *p, Rot *v, Rot *a) {
  r->rot = p;
  r->vel = v;
  r->acc = a;
}

#define ApplyRotation(r) rotateGL(r, 1);
#define CancelRotation(r) rotateGL(r, -1);

#endif
