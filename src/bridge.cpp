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
#include "../include/custom_vertexes.h"

#define ANGLE_MAX 40
#define MIN_WARNING_DELAY 6
#define MAX_WARNING_DELAY 12

Bridge::Bridge(float u, float tEid) 
  : angle_(0.0), full_(false), u_(u), moving_(false), 
    nextWarningTime_(0), nextMoveTime_(0), t_(0), warning_time(tEid)
{
  this->color = 'g';
  srand(time(NULL));
}

Bridge::~Bridge() {}

void Bridge::Render(double R, double D, double L) {
  // glRotatef(angle_,0,1,0);
  float up = 0.0f;
  if (moving_) {
    this->color = 'r';
    up = angle_;
  }
  else if (t_ >= nextWarningTime_) {
    this->color = 'o';
  }
  else {
    this->color = 'g';
  }
  glPushMatrix();
  glRotatef(-90,1,0,0);
  glColor3f(1.0,0.0,1.0);
  glBegin(GL_POLYGON);
  glVertex3f(-L,R,up);
  glVertex3f(-L,R+D,up);
  glVertex3f(-L/2,R+D,0);
  glVertex3f(-L/2,R,0);
  glEnd();
  glPopMatrix();
}

void Bridge::Move(float dt) {
  t_ += dt;
  if (!moving_) {
    if (nextMoveTime_ == 0) {
      nextWarningTime_ = t_ + (rand() % (MAX_WARNING_DELAY + 1 - MIN_WARNING_DELAY)) + MIN_WARNING_DELAY;
      nextMoveTime_ =  nextWarningTime_ + warning_time;
    }
    else if (t_ >= nextMoveTime_) {
      moving_ = true;
      nextWarningTime_ = MAX_WARNING_DELAY + 1;
      nextMoveTime_ = nextWarningTime_ + warning_time;
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
        t_ = 0;
      }
    }
  }
}

void Bridge::Reset(){
  this->angle_ = 0.0;
  this->full_ = false; 
  this->moving_ = false; 
  this->nextWarningTime_ = 0; 
  this->nextMoveTime_ = 0;
  this->t_ = 0;
}

bool Bridge::Moving() {
  return moving_;
}

bool Bridge::Closing(){
  return (this->color == 'o' || this->color == 'r');
}


char Bridge::Get_Color(){
  return this->color;
}

void Bridge::SetTEid(float tEid){
  this->warning_time = tEid;
}

