#include "raylib.h"
int main()
{
    /*
       DELTA TIME
        Time between frames

       WHY IT IS IMPORTANT
         Frame time variations
         Keep movement consistent
        
      SetTargetFPS(60)
        * Sets the target FPS
        * But it doesn't gurantee this value
        * Processes strain the CPU.
        * More strain = lower FPS
        
        Assume:
        1 frame/sec
        velocity = 1 meter/frame

        2 frame/sec
        velocity = 1 meters/frame
        moves 10 meters ahead.
       
       velocity = 1 meter/sec independent of frame rate will be better

      Delta time is the time since the last frame
        * Delta Time = time [Since last frame]
        * If FPS increases, Delta time decreases
        * If FPS decreases, Delta time increases
        * Muliply velocity by DeltaTime, then our velocity is scaled by the amount of time
          between frames.

        GetFrameTime(); -> This is the delta time between frames.

        int gravity {1'000} = The ' is ignored by the compiler so that we can seperate the zeros and make this more redable to humans.

        Multiplied by dT(Delta time) when:
         Updating position with velocity
         Updating velocity with acceleration
   */

    const int Window_Width{512};
    const int Window_Height{380};
    
    // Initialise the window and use this before while loop
    InitWindow(Window_Width,Window_Height,"Dapper Dasher");

    int velocity{0}; //Pixles per frame
    
    // Acceleration due to gravity (pixles/second)/second
    const int gravity {1'000}; 

    // Compound datatype which has it's own variables, we use the dot . operator to access compund datatype
    // LoadTexture Takes the file path as an input parameter.
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec; // Texture rec needs an rectangle describing which section of the sprite sheet to draw.
    scarfyRec.width = scarfy.width/6; // 6 Because there are 6 images
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos; // For the position 
    scarfyPos.x = Window_Width/2 - scarfyRec.width/2;
    scarfyPos.y = Window_Height - scarfyRec.height;
    
    /*
      scarfy. => To access the inbuilt variables.
    */

    // Create a variable for in the air
    bool isInAir {};

    // Jump Velocity (pixles/second)
    const int jumpVel{-600};

    SetTargetFPS(60);
    
    // Keeping the WindowShouldClose as false.
    // Simple words negating the statement
    // We use the negation operator
    while(!WindowShouldClose())
    {
      // Delta time 
      const float dT{GetFrameTime()};
      // Start Drawing
      BeginDrawing();
      ClearBackground(WHITE);
      
      // Perform ground check
      if (scarfyPos.y >= Window_Height - scarfyRec.height)
      {
        // Scarfy on the ground
        velocity = 0;
        
        // Create a variable for in the air
        isInAir = false;
      }
      else
      {
        // Scarfy on the air
         velocity += gravity * dT;
         isInAir = true;
      }

      // Jump Check
      if(IsKeyPressed(KEY_SPACE) && !isInAir) // !isInAir meaning not in Air.
      {
        velocity +=jumpVel; // It jumps to jumpvel value
      }
      
      scarfyPos.y +=velocity * dT; // Update The pos y changes as adding with velocity.

      DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
      // Finish Drawing
      EndDrawing();
    }

    UnloadTexture(scarfy); // Unload texture from GPU memory (VRAM)
    // Raylibs new function
    /*If we want to do things technically the CloseWindow()
      take care of shutting down the window properly before
      the program terminates.
    */
    CloseWindow();
}