#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include "GL/freeglut.h"
#include "../include/CarModel.h"

CarModel::CarModel(float u, float u_max, Model* model,
  float startX, float startY, float startZ)
  : Vehicle(u, u_max), model_(model),
    startX_(startX), startY_(startY), startZ_(startZ) {}

CarModel::~CarModel()
{}

void CarModel::Render(double R, double D, double L)
{
  glPushMatrix();

  glTranslatef(startX_, startY_, startZ_);
  glTranslatef(x_, 0, 0);
  glScalef(0.3,0.3,0.3);
  glColor3f(0.1f, 0.3f, 0.3f);
  glRotatef(-90,1.0,0.0,0.0);
  glRotatef(180,0.0,0.0,1.0);
  model_->Render();

  glPopMatrix();
}

bool CarModel::ReachedPosition(float x, float y1, float y2) {
  if (x_ >= x) {
    return true;
  }
  return false;
}
