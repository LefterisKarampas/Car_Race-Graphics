#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include "GL/freeglut.h"
#include "../include/vehicle.h"
#include "../include/visuals.h"

Vehicle::Vehicle(float u, float u_max, float uOp)
  : x_(0.0f), z_(0.0f), u_(u), u_max_(u_max), uOp_(uOp),
    theta_(0), turning_(false), direction_(1),
    up_(false), down_(false), crash_(false) {}

Vehicle::~Vehicle() {}

void Vehicle::Reset(float u) {
  x_ = 0.0f;
  z_ = 0.0f;
  u_ = u;
  theta_ = 0;
  turning_ = false;
  direction_ = 1;
  up_ = false;
  down_ = false;
  crash_ = false;
}

void Vehicle::ForwardLeft(float dt) {
  theta_ = M_PI;
  up_ = false;
  down_ = false;
  direction_ = -1;
  x_ -= u_ * dt;
  turning_ = false;
  crash_ = false;
}

void Vehicle::ForwardRight(float dt) {
  z_ = 0.0f;
  up_ = false;
  down_ = false;
  theta_ = 0;
  direction_ = 1;
  x_ += u_ * dt;
  turning_ = false;
  crash_ = false;
}

void Vehicle::TurnDown(float radius, float dt) {
  if (!turning_) {
    // just started turning
    xBeforeTurn_ = x_;
    zBeforeTurn_ = z_;
  }

  up_ = false;
  down_ = true;
  float omega = u_ / radius;
  theta_ += omega * dt;
  x_ = xBeforeTurn_ + radius * sinf(theta_);
  z_ = zBeforeTurn_ + radius * (1 + cosf(theta_));
  turning_ = true;

  crash_ = (u_ >= uOp_);
}

void Vehicle::TurnUp(float radius, float dt) {
  if (!turning_) {
    // just started turning
    xBeforeTurn_ = x_;
    zBeforeTurn_ = z_;
  }

  up_ = true;
  down_ = false;
  float omega = u_ / radius;
  theta_ += omega * dt;
  x_ = xBeforeTurn_ + radius * sinf(theta_);
  z_ = zBeforeTurn_ + radius * (cosf(theta_) - 1);
  turning_ = true;

  crash_ = (u_ >= uOp_);
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

void Vehicle::SetSpeed(float u) {
  u_ = u;
}

float Vehicle::GetSpeed() {
  return u_;
}

void Vehicle::Stop() {
  u_ = 0;
}