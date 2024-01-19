#include "raylib.h"
int main()
{
    /*
      What is gravity ?
       -> It is a downward force.
       -> Pulling objects toward the ground.
       -> Impart an acceleration.

       F=ma mass x accelaration

       What is acceleration ?
        -> Velocity = Change in position
        -> Acceleration = change in velocity
        -> All objects accelerate at 9.8 m/s per second.
                                      512      
     0 ********************************* X 
       *
       *
       * 
       * 
       * 
       * 
     Y * 380    
    */
    const int Window_Width{512};
    const int Window_Height{380};
    
    // Initialise the window and use this before while loop
    InitWindow(Window_Width,Window_Height,"Dapper Dasher");

    // Rectangle dimension
    const int width{50};
    const int height{80};

    int posY{Window_Height - height};
    int velocity{0}; //Pixles per frame
    
    // Acceleration due to gravity (pixles/frame)/frame
    const int gravity {1};

    SetTargetFPS(60);
    
    // Keeping the WindowShouldClose as false.
    // Simple words negating the statement
    // We use the negation operator
    while(!WindowShouldClose())
    {
      // Start Drawing
      BeginDrawing();
      ClearBackground(WHITE);
      
      // Perform ground check
      if (posY >= Window_Height - height)
      {
        // Rectangle on the ground
        velocity = 0;
      }
      else
      {
        // Rectangle on the air
         velocity += gravity;
      }
      if(IsKeyPressed(KEY_SPACE))
      {
        velocity -=10; // It jumps to -10
      }
      
      posY +=velocity; // Update The pos y changes as adding with velocity.

      DrawRectangle(Window_Width/2, posY, width, height, BLUE);
      // Finish Drawing
      EndDrawing();
    }
    // Raylibs new function
    /*If we want to do things technically the CloseWindow()
      take care of shutting down the window properly before
      the program terminates.
    */
    CloseWindow();
}