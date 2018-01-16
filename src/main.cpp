#include <stdio.h>     		
#include <cstring>	
#include "GL/freeglut.h"            
#include "../include/visuals.h" 


char * light_input;
char *car_input;
void read_args(int , char **,char ** ,char **);

int main(int argc, char* argv[])
{ 
  // initialize GLUT library state
  glutInit(&argc, argv);
	
  // Set up the display using the GLUT functions to 
  // get rid of the window setup details:
  // - Use true RGB colour mode ( and transparency )
  // - Enable double buffering for faster window update
  // - Allocate a Depth-Buffer in the system memory or 
  //   in the video memory if 3D acceleration available	
                      //RGBA//DEPTH BUFFER//DOUBLE BUFFER//
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
 
  
  // Define the main window size and initial position 
  // ( upper left corner, boundaries included )
  glutInitWindowSize(480,480);
  glutInitWindowPosition(50,50);
  
  // Create and label the main window
  glutCreateWindow("Race_Car");

  read_args(argc,argv,&light_input,&car_input);
  
  // Configure various properties of the OpenGL rendering context
  Setup();
  // Callbacks for the GL and GLUT events:

  // The rendering function 
  glutDisplayFunc(Render);
  glutReshapeFunc(Resize);
  glutIdleFunc(Idle);
  glutSpecialFunc(Keyboard);
  glutKeyboardFunc(MyKeyboardFunc);
  glutMouseFunc(Mouse);

  glutCreateMenu(SelectPlayers);
  glutAddMenuEntry("1 Player",PLAYER1);
  glutAddMenuEntry("2 Players",PLAYER2);
  glutAttachMenu(GLUT_LEFT_BUTTON);


  glutCreateMenu(SelectLevel);
  glutAddMenuEntry("Easy",EASY);
  glutAddMenuEntry("Medium",MEDIUM);
  glutAddMenuEntry("Hard",HARD);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  //Enter main event handling loop
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