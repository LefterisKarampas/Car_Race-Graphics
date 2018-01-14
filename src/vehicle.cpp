#include "../include/vehicle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include "GL/freeglut.h"
#include "../include/visuals.h"
#include "../include/Model.h"

Vehicle::Vehicle(float u, float u_max)
  : x_(0.0f), z_(0.0f), u_(u), u_max_(u_max),
    theta_(0), turning_(false), direction_(1) {}

Vehicle::~Vehicle() {}

void Vehicle::ForwardLeft(float dt) {
  theta_ = 0;
  direction_ = -1;
  x_ -= u_ * dt;
  turning_ = false;
}

void Vehicle::ForwardRight(float dt) {
  theta_ = 0;
  direction_ = 1;
  x_ += u_ * dt;
  turning_ = false;
}

void Vehicle::TurnDown(float radius, float dt) {
  if (!turning_) {
    // just started turning
    theta_ = 0;
    xBeforeTurn_ = x_;
    zBeforeTurn_ = z_;
  }

  float omega = u_ / radius;
  theta_ -= omega * dt;
  x_ = xBeforeTurn_ + radius * sinf(theta_);
  z_ = zBeforeTurn_ + radius * (cosf(theta_) - 1);
  turning_ = true;
  if (theta_ > (-1)* M_PI / 2) {
    direction_ = -1;  
  }
  else {
    direction_ = 1;
  }
}

void Vehicle::TurnUp(float radius, float dt) {
  if (!turning_) {
    // just started turning
    theta_ = 0; // to right
    xBeforeTurn_ = x_;
    zBeforeTurn_ = z_;
  }

  float omega = u_ / radius;
  theta_ += omega * dt;
  x_ = xBeforeTurn_ + radius * sinf(theta_);
  z_ = zBeforeTurn_ + radius * (1 - cosf(theta_));
  turning_ = true;
  if (theta_ < M_PI / 2) {
    direction_ = 1;  
  }
  else {
    direction_ = -1;
  }
}


bool Vehicle::Moving() {
  return (u_ == 0);
}

void Vehicle::SpeedUp(float a) {
  u_ += a;
  if (u_ > u_max_) {
    u_ = u_max_;
  }
}

void Vehicle::SpeedDown(float a) {
  u_ -= a;
  if (u_ < 0) {
    u_ = 0;
  }
}