#define EASY 0
#define MEDIUM 1
#define HARD 2

#define PLAYER1 1
#define PLAYER2 2



//-------- Functions --------------------------------

void Render();
// The function responsible for drawing everything in the 
// OpenGL context associated to a window. 

void Resize(int w, int h);
// Handle the window size changes and define the world coordinate 
// system and projection type

void Setup();
// Set up the OpenGL state machine and create a light source

void Idle();

 
void Keyboard(int key,int x,int y);
// Function for handling keyboard events.

void Mouse(int button,int state,int x,int y); 
// Function for handling mouse events

void SelectLevel(int choice);

void SelectPlayers(int choice);

void MyKeyboardFunc(unsigned char Key, int x, int y);

void print_velocity(float current);