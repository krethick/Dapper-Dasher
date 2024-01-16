#include "raylib.h"
int main()
{
    /*
      Velocity and Jumping
      
      What is Velocity ?
      -> Speed in a certain direction
      -> Distance over time. (m/s)

      If positive the velocity is 10 (m/s)
      If negative the velocity is -10 (m/s)

      We are working in pixles i.e pixles/frame
      
      Eg: 10 (p/f) x 60 (f/s) = 600 (p/s)

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

    SetTargetFPS(60);
    
    // Keeping the WindowShouldClose as false.
    // Simple words negating the statement
    // We use the negation operator
    while(!WindowShouldClose())
    {
      // Start Drawing
      BeginDrawing();
      ClearBackground(WHITE);
      
      if(IsKeyPressed(KEY_SPACE))
      {
        velocity -=10; // It jumps to -10
      }

      posY +=velocity; // The pos y changes as adding with velocity.

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