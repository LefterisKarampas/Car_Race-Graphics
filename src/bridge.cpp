#include "../include/bridge.h"
#include <stdio.h>     // - Just for some ASCII messages
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include "GL/freeglut.h"   // - An interface and windows management library
#include "../include/visuals.h"   // Header file for our OpenGL functions
#include "../include/Model.h"
#include "../include/custom_vertexes.h"

#define ANGLE_MAX 6
#define MIN_WARNING_DELAY 2
#define MAX_WARNING_DELAY 6
#define WARNING_TIME 3

Bridge::Bridge(float u) 
  : angle_(0.0), full_(false), u_(u), moving_(false), 
    nextWarningTime_(0), nextMoveTime_(0)
{
  srand(time(NULL));
}

Bridge::~Bridge() {}

void Bridge::Render(double R, double D, double L) {
  glPushMatrix();
  glRotatef(angle_,0,1,0);
  if (moving_) {
    glColor3f(1.0,0.0,0.0);
  }
  else if (time(NULL) >= nextWarningTime_) {
   glColor3f(1.0,0.5,0.0); 
  }
  else {
   glColor3f(0.0,1.0,0.0);  
  }

  glRectf(-L,R,-L/2,R+D);
  glEnd();
  glPopMatrix();
}
void Bridge::Move(float dt) {
  if (!moving_) {
    if (nextMoveTime_ == (time_t) 0) {
      nextWarningTime_ = time(NULL) + (rand() % (MAX_WARNING_DELAY + 1 - MIN_WARNING_DELAY)) + MIN_WARNING_DELAY;
      nextMoveTime_ =  nextWarningTime_ + WARNING_TIME;
    }
    else if (time(NULL) >= nextMoveTime_) {
      moving_ = true;
      nextWarningTime_ = 0;
      nextMoveTime_ = 0;
    }
  }
  else {
    if(!full_){
      angle_ += u_ * dt;
      if(angle_ > ANGLE_MAX){
        full_ = true;
        angle_ = ANGLE_MAX - 1;
      }
    }
    else{
      angle_ -= u_ * dt;
      if(angle_ < 0){
        full_ = false;
        moving_ = false;
        angle_ = 0;
      }
    }
  }
}

bool Bridge::Moving() {
  return moving_;
}