#ifndef GAMA_DRAWSHAPE_INCLUDED
#define GAMA_DRAWSHAPE_INCLUDED

#include "color.h"
#include "rotation.h"
#include "vector.h"
#include <GL/gl.h>
#include <math.h>

void drawRectangle(Pos *t, Rot *r, double width, double height, Color color) {
  Pos _t;
  _t.x = width / 2.0;
  _t.y = height / 2.0;
  SetGLColor(color);
  double w = width / 2.0f;
  double h = height / 2.0f;
  {
    ApplyTranslation(&_t);
    ApplyTranslation(t);
    ApplyRotation(r);

    {
      glBegin(GL_QUADS);
      {

        glVertex2f(-w, -h); // top left
        glVertex2f(+w, -h); // top right
        glVertex2f(+w, +h); // bottom right
        glVertex2f(-w, +h); // bottom left
      }
      glEnd();
    }
    CancelRotation(r);
    CancelTranslation(t);
    CancelTranslation(&_t);
  }
}
void drawCircle(double cx, double cy, double radius, Color color) {
  double x, y;
  double step = 0.1;
  double angle = -step;
  SetGLColor(color);
  glBegin(GL_TRIANGLE_FAN);
  {
    glVertex2f(cx, cy);
    do {
      x = sin(angle) * radius;
      y = cos(angle) * radius;
      glVertex2f(cx + x, cy + y);

      angle += step;
    } while (angle < 2 * PI);
  }
  glEnd();
}

#endif
