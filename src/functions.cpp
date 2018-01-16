#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include "GL/freeglut.h"
#include "../include/visuals.h"
#include "../include/bridge.h"
#include "../include/vehicle.h"
#include "../include/Score.h"
#include "../include/CarModel.h"
#include "../include/functions.h"

extern float dt;
extern float vA;
extern float vOr;
extern float vMax;
extern float tEid;
extern float a;
extern float d;
extern float dtMax;

//Grid parameters
extern double R;
extern double D;
extern double L;

//turns coordinates
extern float* turns;
extern int next_turn;

extern Score score;

//Vehicle object
extern CarModel* car_model1;
extern CarModel* car_model2;
extern Bridge *bridge;

extern int count;
extern bool reset;
extern int start;
extern int v;
extern float eye_y;
extern float eye_z;
extern float board_rotate;
extern int dif_level;
extern int players;
extern int print_flag;

void Keyboard(int key,int x,int y)
{ 
  if(start){
    switch(key)
    {
      case GLUT_KEY_LEFT:
        car_model1->SpeedDown(d);
        break;
      case GLUT_KEY_RIGHT:
        car_model1->SpeedUp(a);
        break;
      case GLUT_KEY_UP:
        if (dt >= 2.0f) {
          dt += 0.1f;
        }
        else {
          dt += 0.2f; 
        }
        if (dt > dtMax) {
          dt = dtMax;
        }
        break;
      case GLUT_KEY_DOWN:
        if (dt <= 2.0f) {
          dt -= 0.1f;
        }
        else {
          dt -= 0.2f; 
        }
        if (dt < 1) {
          dt = 1;
        }
        break;
      default: 
        return;
    }
  }
  glutPostRedisplay();

}


void SelectLevel(int choice)
{
  switch (choice) {
    case EASY : 
      d = 7; 
      tEid = 13;
      vOr = 50;
      car_model1->SetvOr(vOr);
      car_model2->SetvOr(vOr);
      bridge->SetTEid(tEid);
      reset = true;
      count = COUNTDOWN;
      start = 0;
      dif_level = choice;
      break;
    case MEDIUM : 
      d = 4; 
      tEid = 10;
      vOr = 40;
      car_model1->SetvOr(vOr);
      car_model2->SetvOr(vOr);
      bridge->SetTEid(tEid);
      reset = true;
      count = COUNTDOWN;
      start = 0;
      dif_level = choice;
      break;
    case HARD :
      d = a;
      tEid = 7;
      vOr = 30;
      car_model1->SetvOr(vOr);
      car_model2->SetvOr(vOr);
      bridge->SetTEid(tEid);
      reset = true;
      count = COUNTDOWN;
      start = 0;
      dif_level = choice;
      break;
  }
}


void SelectPlayers(int choice)
{
  switch (choice) {
    case PLAYER1 : 
      players = PLAYER1;
      reset = true;
      count = COUNTDOWN;
      start = 0;
      break;
    case PLAYER2 : 
      players = PLAYER2;
      reset = true;
      count = COUNTDOWN;
      start = 0;
      break;
  }
}


void MyKeyboardFunc(unsigned char Key, int x, int y){
  switch(Key){
    case 's':{
      start = (start +1) % 2;
      reset = false;
      count = 0;
      break;
    }
    case 32:{ //SPACEBAR
      reset = true;
      count = COUNTDOWN;
      start = 0;
      break;
    }
    //Change Camera
    case 'v':{
      v = (v+1) % 2;
      if(v == 0){
        eye_y = 300.0f;
        eye_z = 380.0f;
        board_rotate = 0;
      }
      else{
        eye_y = 1000.0f;
        eye_z = 100.0f;
        board_rotate = -55;
      }
      break;
    }
    case 'e':{
      dif_level = (dif_level +1) % 3;
      SelectLevel(dif_level);
      break;
    }
    case 'a':{
      if((players == PLAYER2) && start){
        car_model2->SpeedDown(d);
      }
      break;
    }
    case 'd':{
      if((players == PLAYER2) && start){
        car_model2->SpeedUp(a);
      }
      break;
    }
    case 'p':{
      if(players == PLAYER1){
        SelectPlayers(PLAYER2);
      }
      else{
        SelectPlayers(PLAYER1);
      }
      break;
    }
    case 'x':{
      print_flag = (print_flag +1) % 2;
      break;
    }
    case 'q': {
      score.SaveScore();
      free(turns);
      exit(0);
      break;
    }
  }
  glutPostRedisplay();
}

void ShowInformation(float current){

  char str[128];
  glPushMatrix();
  glTranslatef(0,-80,-400);
  if(print_flag){
    sprintf(str,"Time elapsed: %.2lf",car_model1->GetTime()/10.0);
  }
  else{
    sprintf(str,"Current Velocity: %.2lf",current);
  }
  if(v){
    glScalef(1.5,1.5,1.5);
  }
  else{
    glScalef(1.2,1.2,1.2);
  }
  glRotatef(board_rotate,1,0,0);

  glPushMatrix();
  glTranslatef(-4*L,0,-0);
  glScalef(4.5,4.5,4.5);
  glRotatef(-20,1,0,0);
  //glRotatef(-20,0,1,0);
  glColor3f(0.5,1.0,0.5);
  glTranslatef(30,28.0,0.0);
  GLfloat size = 0.05f;
  glScalef(size,size,size);
  for (int i=0;i<strlen(str);i++){
    glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
  }
  glPopMatrix();


  if(print_flag){
    sprintf(str,"dt: %.1lf",dt);
  }
  else{
    sprintf(str,"Vop: %.2lf",vOr);
  }
  glPushMatrix();
  glTranslatef(-4*L,-L/2,0);
  glScalef(4.5,4.5,4.5);
  glRotatef(-20,1,0,0);
  //glRotatef(-20,0,1,0);
  glColor3f(1.0,0.0,0.0);
  glTranslatef(30,28.0,0.0);
  glScalef(size,size,size);
  for (int i=0;i<strlen(str);i++){
    glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
  }
  glPopMatrix();


  glPopMatrix();
}