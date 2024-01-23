#include "raylib.h"
int main()
{
    /*
      Create a Nebula Hazard
      
      * We can actually start off the nebula off the scree, which
        should be pretty easy because a textures position is its 
        upper left corner.
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

   // Create a Nebula
   Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
   Rectangle nebulaRec;
   nebulaRec.width = nebulaRec.width/8;
   nebulaRec.height = nebulaRec.height/8;
   nebulaRec.x = 0;
   nebulaRec.y = 0;
   Vector2 nebPos; //

    // Animation Frame
    int frame{}; // Braced initialisation as the value starts with 0.

    // Create a variable for in the air
    bool isInAir {};

    // Jump Velocity (pixles/second)
    const int jumpVel{-600};
    
    // Amount of time before we update the animation frame
    const float updateTime{1.0/12.0};
    
    float runningTime{}; 
    
    
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
      
      // Update Running time
      runningTime += dT;
      
      if(runningTime>=updateTime)
      {
          runningTime = 0.0;
          
          // Update animation frame
          scarfyRec.x = frame * scarfyRec.width;
          frame++; // Next time the frame will be increasing by 1
          
          /* 
          We need to reset the frame as soon as it gets larger than five, 
          since we have only frames 0 through five on the sprite sheet so 
          we can place an if check to see if frame is larger than 5, if yes
          we'll simply set it back to Zero.
        */
      if(frame>5) 
      {
        frame = 0;
      }
    }
     
    

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
   UnloadTexture(nebula);
    CloseWindow();
}