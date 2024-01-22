#include "raylib.h"
int main()
{
    /*
      DRAWING FROM SPRITE SHEETS


    */
    const int Window_Width{512};
    const int Window_Height{380};
    
    // Initialise the window and use this before while loop
    InitWindow(Window_Width,Window_Height,"Dapper Dasher");

    int velocity{0}; //Pixles per frame
    
    // Acceleration due to gravity (pixles/frame)/frame
    const int gravity {1};

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

    // Jump Velocity
    const int jumpVel{-22};

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
         velocity += gravity;
         isInAir = true;
      }

      // Jump Check
      if(IsKeyPressed(KEY_SPACE) && !isInAir) // !isInAir meaning not in Air.
      {
        velocity +=jumpVel; // It jumps to jumpvel value
      }
      
      scarfyPos.y +=velocity; // Update The pos y changes as adding with velocity.

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