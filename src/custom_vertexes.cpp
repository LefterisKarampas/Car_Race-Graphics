#include "../include/custom_vertexes.h"
#include <stdio.h>     // - Just for some ASCII messages
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include "GL/freeglut.h"   // - An interface and windows management library
#include "../include/visuals.h"   // Header file for our OpenGL functions

void increase(int* i) {
  *i = *i + 1;
}
void decrease(int* i) {
  *i = *i - 1;
}

void SemiCircleVertexes(float cx, float cy, float r, int num_segments, bool rightSemi, bool startUp) {
    int start;
    if (startUp) {
      start = num_segments / 4; // this makes first theta pi/2
      //and makes us start from bottom point
    }
    else {
      start = 0; // this makes first theta 0
      //and makes us start from top point
      rightSemi = !rightSemi; //to reverse direction
    }

    int ii = start;
    bool startOk = false;

    void (*changeI)(int*);
    int loopEnd;
    int loopReset;

    if (rightSemi) {
      changeI = increase; // go up
      loopEnd = num_segments;
      loopReset = 0;
    }
    else {
      changeI = decrease; // go down
      loopEnd = -1;
      loopReset = num_segments - 1;
    }

    while (1) {
      if (!startOk) {
        startOk = true;
      }
      else if (ii == start) {
        break;
      }
      else if (ii == loopEnd) {
        ii = loopReset;
        continue;
      }

      float theta = 2.0f * M_PI * float(ii) / float(num_segments);//get the current angle 
      float x = r * cosf(theta);//calculate the x component 
      float y = r * sinf(theta);//calculate the y component

      if(cx > 0){
        if(x+cx < cx){
          changeI(&ii);
          continue;
        }
      }
      else {
        if(x+cx > cx){
          changeI(&ii);
          continue;
        }
      }
      glVertex2f(x + cx, y + cy);//output vertex 
      changeI(&ii);
    }
}

void TwoSemiCirclesVertexes(float cx, float cy, float r1, float r2, int num_segments, bool rightSemi) {
    int start;
    
    void (*changeI)(int*);
    int loopEnd;
    int loopReset;

    if (rightSemi) {
      start = num_segments / 4; // this makes first theta pi/2
      //so we start from down point
      changeI = increase; // go up
      loopEnd = num_segments;
      loopReset = 0;
    }
    else {
      start = 0; // this makes first theta 0
      //so we start from up point
      changeI = decrease; // go down
      loopEnd = -1;
      loopReset = num_segments - 1;
    }

    int ii = start;
    bool startOk = false;

    while (1) {
      if (!startOk) {
        startOk = true;
      }
      else if (ii == start) {
        break;
      }
      else if (ii == loopEnd) {
        ii = loopReset;
        continue;
      }

      float theta = 2.0f * M_PI * float(ii) / float(num_segments);//get the current angle 
      float cos = cosf(theta);//calculate the x component 
      float sin = sinf(theta);//calculate the y component

      if(cx > 0){
        if(cos < 0){
          changeI(&ii);
          continue;
        }
      }
      else {
        if(cos > 0){
          changeI(&ii);
          continue;
        }
      }
      glVertex2f(cx + r1*cos, cy + r1*sin);//output vertex for first semi
      glVertex2f(cx + r2*cos, cy + r2*sin);//output vertex for second semi
      changeI(&ii);
    }
}