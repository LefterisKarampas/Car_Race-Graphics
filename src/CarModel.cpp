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
    startX_(startX), startY_(startY), startZ_(startZ),
    turning_(false), next_turn(0) {}

CarModel::~CarModel()
{}

void CarModel::Render(double R, double D, double L)
{
  glPushMatrix();

  glTranslatef(startX_, startY_, startZ_);
  glTranslatef(x_, 0, z_);
  glScalef(0.3,0.3,0.3);
  glColor3f(0.1f, 0.3f, 0.3f);
  glRotatef(-90,1.0,0.0,0.0);
  glRotatef(180,0.0,0.0,1.0);
  float degrees = theta_ * 180 / M_PI;
  glRotatef(degrees,0.0,0.0,1.0);
  model_->Render();

  glPopMatrix();
}

bool CarModel::ReachedPosition(float x) {
  // fprintf(stderr, "%d x_ %f trying to reach %f\n", direction_, x_, x);
  if (turning_) {
    if (up_) {
      return x >= x_;
    }
    else {
      return x <= x_;
    }
  }
  else {
    if (direction_ == 1) {
      return x <= x_;
    }
    else {
      return x >= x_;
    }
  }
}

void CarModel::Move(float* turns, float radius, float dt) {
  if (!turning_) {
    if (next_turn == 0) {
      ForwardRight(dt);
    }
    else {
      ForwardLeft(dt);
    }
    if (ReachedPosition(turns[next_turn])) 
    {
        turning_ = true;
    }
  }
  else {
    if (next_turn == 0) {
      TurnUp(radius, dt);
    }
    else {
      TurnDown(radius, dt);

    }
    if (ReachedPosition(turns[next_turn])) 
    {
        turning_ = false;
        next_turn = (next_turn + 1) % 2;
    }
  }
}