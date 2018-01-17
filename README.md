# Car_Race-Graphics
Car Race for Graphics Assignment on OpenGL

## 1) Requirements
    
    sudo apt-get install freeglut3 freeglut3-dev  
    
## 2)Run game
    mkdir -p build
    make
    ./build/race -l Models/trafficlight.obj -c Models/clk.obj
    
Press s for starting the race!
    
## 3)Guide
Win the game by finishing first on 3 rounds without crashing on the bridge or getting out of the turn due to high speed.
You can change the difficulty level, the camera view or the game speed time.
   
## 4) Keyboard
   ### Player 1
       Right Arrow - Increase the velocity
       Left Arrow - Decrease the velocity
       
    ### Game 
        Up Arrow - Increase the dt
        Down Arrow - Decrease dt
        s - Start/Stop game
        v - Change camera view
        x - Change info
        p - Select 1 player or 2 players
        e - Change difficulty level (EASY,MEDIUM,HARD)
        q - Save the score and quit the game
        SPACEBAR - Restart the game
        
   ### Player 2
       d - Increase the velocity for player 2 (2 players mode)
       a - Decrease the velocity for player 2 (2 players mode)
    
## 5) Mouse
    Right Click - Difficulty Menu
    Left Click - Player Menu
