#include <stdio.h>     		
#include <cstring>	
#include "GL/freeglut.h"      
#include "../include/visuals.h"
#include "../include/functions.h"


char * light_input;
char *car_input;
void read_args(int , char **,char ** ,char **);

int main(int argc, char* argv[])
{ 
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
 
  
  glutInitWindowSize(480,480);
  glutInitWindowPosition(50,50);
  
  glutCreateWindow("Race_Car");

  read_args(argc,argv,&light_input,&car_input);
  
  Setup();
  
  glutDisplayFunc(Render);
  glutReshapeFunc(Resize);
  glutIdleFunc(Idle);
  glutSpecialFunc(Keyboard);
  glutKeyboardFunc(MyKeyboardFunc);
  // glutMouseFunc(Mouse);

  glutCreateMenu(SelectPlayers);
  glutAddMenuEntry("1 Player",PLAYER1);
  glutAddMenuEntry("2 Players",PLAYER2);
  glutAttachMenu(GLUT_LEFT_BUTTON);


  glutCreateMenu(SelectLevel);
  glutAddMenuEntry("Easy",EASY);
  glutAddMenuEntry("Medium",MEDIUM);
  glutAddMenuEntry("Hard",HARD);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutMainLoop();
  return 0;	
}  



void Usage(char *exec){
  fprintf(stderr,"Usage: %s -l <traffic_light model> -c <car model>\n",exec);
}


void read_args(int argc, char **argv,char ** light_input,char **car_input){
  int i=1;
  while(i < argc){
    if(!strcmp(argv[i],"-l")){
      *light_input = argv[i+1];
    }
    else if(!strcmp(argv[i],"-c")){
      *car_input = argv[i+1];
    }
    else{
      Usage(argv[0]);
      exit(1);
    }
    i+=2;
  }

  if(light_input == NULL || car_input == NULL){
    Usage(argv[0]);
    exit(1);
  }
}