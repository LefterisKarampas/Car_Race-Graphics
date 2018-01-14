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
    theta_(0), t_(0), turning_(false), direction_(1) {}

Vehicle::~Vehicle() {}

void Vehicle::Forward(float dt) {
  x_ += (u_ * direction_) * dt;
  turning_ = false;
}

void Vehicle::Turn(float radius, float dt) {
  if (!turning_) {
    // just started turning
    direction_ *= -1; // switch direction
    t_ = 0; // reset time
    theta_ = M_PI;
    xOld_ = x_;
    zOld_ = z_;
  }

  t_ += dt;
  fprintf(stderr, "In turn\n");
  float omega = (u_ * direction_) / radius;
  theta_ += omega * dt;
  fprintf(stderr, "theta %f\n", theta_);
  x_ = xOld_ + radius * sinf(theta_);
  z_ = zOld_ + radius * (cosf(theta_) + 1);
  turning_ = true;
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