#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include "GL/freeglut.h"
#include "../include/test_car.h"
#include "../include/visuals.h"

#define NOSE_RATIOA 0.8f
#define NOSE_RATIOB 0.6f

TestCar::TestCar(float u, float u_max, float hRatio, 
          float lRatio, float dRatio)
  : Vehicle(u, u_max), hR_(hRatio), lR_(lRatio), dR_(dRatio) {}

TestCar::~TestCar() {}

void TestCar::Render(float startX, float startY, double R, double D, double L) {
  float length = L * lR_;
  float height = D * hR_;
  if (direction_ == 1) {
    noseX_ = startX + x_ + length;
    noseY_ = startY + z_ + height;
  }
  else {
    noseX_ = startX + x_;
    noseY_ = startY + z_;
  }

  glPushMatrix();

  // some z corrections
  if (z_ > 2*(R + D) - height) {
    z_ = 2*(R + D) - height;
  }
  else if (z_ < 0) {
    z_ = 0;
  }

  float toCenterX;
  if (theta_ != 0) {
    if (x_ > 0) {
      toCenterX = L;
    }
    else {
      toCenterX = -L;
    }
  }
  // glTranslatef(toCenterX, 0.0f, 0.0f); // move back to center
  // double degrees = theta_ * 180 / M_PI;
  // fprintf(stderr, "%f %f\n", theta_, degrees);
  // glRotatef(degrees,0.0f,0.0f,1.0f); // rotate
  // glTranslatef(-toCenterX, 0.0f, 0.0f); // move back to center
  glTranslatef(x_, z_, 0.0f); // move

  glBegin(GL_POLYGON);
  
  glColor3f(1.0f,0.0f,0.0f);
  glVertex3f(startX, startY + height, 0.0f);
  glVertex3f(startX + length, startY + height, 0.0f);
  // glVertex3f(startX + (length * NOSE_RATIOA), startY + height, 0.0f);
  
  // glVertex3f(startX + length, startY + (height * NOSE_RATIOB), 0.0f);
  
  glColor3f(0.0f,100.0f,0.0f);
  glVertex3f(startX + length, startY, 0.0f);
  glColor3f(0.0f,0.0f,100.0f);
  glVertex3f(startX, startY, 0.0f);

  glEnd();
  // drawBall();
  glPopMatrix();

}

bool TestCar::ReachedPosition(float x, float y1, float y2) {
  // fprintf(stderr, "x %f %d NoseX %f NoseY %f x %f y1 %f y2 %f\n",
  //         x_, direction_, noseX_, noseY_, x, y1, y2);
  if (direction_ == 1) {
    return (noseX_ >= x && noseY_ >= y1 && noseY_ <= y2);
  }
  else {
    return (noseX_ <= x && noseY_ >= y1 && noseY_ <= y2); 
  }
}

void TestCar::ResetDirection() {
  direction_ = 1;
}

float TestCar::MinusHeight(float D, float num) {
  float height = D * hR_;
  return num - height;
}

void TestCar::drawBall() {
  float ballX = -50.0f;
  float ballY = 0.0f;
  float ballZ = 0.0f;

  glColor3f(0.0, 1.0, 0.0); //set ball colour
  glTranslatef(ballX,ballY,ballZ); //moving it toward the screen a bit on creation
  //glRotatef(ballX,ballX,ballY,ballZ);
  glutSolidSphere (30, 2000, 2000); //create ball.
  glTranslatef(ballX+150.0f,ballY,ballZ); //moving it toward the screen a bit on creation
  glutSolidSphere (30, 2000, 2000); //
}