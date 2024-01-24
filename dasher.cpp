#include "raylib.h"
int main()
{
    /*
     Multiple Nebula Hazard
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
   Rectangle nebulaRec{0.0, 0.0, nebula.width/8, nebula.height/8};
   Vector2 nebPos{Window_Width, Window_Height-nebulaRec.height}; // For the position 

   // Create a Second Nebula
   Rectangle nebula2Rec{0.0, 0.0, nebula.width/8, nebula.height/8};
   Vector2 neb2Pos{Window_Width + 300, Window_Height-nebulaRec.height}; // For the position , + 300 because to move away from the second nebula
   
    // Nebula Animation Variable
    int nebFrame{}; // Nebula Frame
    const float nebUpdateTime{1.0/12.0}; // Nebula Update Time
    float nebRunningTime{}; // Nebula Running Time
    
    int neb2Frame{}; // Nebula Frame 2
    const float neb2UpdateTime{1.0/16.0}; // Nebula2 Update Time (16 because to cycle the animation faster)
    float neb2RunningTime{}; // Nebula2 Running Time
    // nebula X velocity (pixles/second)
    int nebVel{-200}; // Nebula Velocity

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

      // Update Nebula Position
      nebPos.x += nebVel * dT; // We use dT to make it frame rate independent

      // Update Second Nebula Position
      neb2Pos.x += nebVel * dT; // We use dT to make it frame rate independent

      // Update Scarfy Position
      scarfyPos.y +=velocity * dT; // Update The pos y changes as adding with velocity.
      
      if(!isInAir) // !isInAir = Not in Air i.e !True = false 
      {
      // Update Running time
      runningTime += dT;
      if(runningTime>=updateTime) // We can even put this (isInAir==false) if we want.
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
      }
      
      // Update Nebula Running time
      nebRunningTime += dT;
      if(nebRunningTime>=nebUpdateTime)
      {
        nebRunningTime = 0.0;
        // Update animation frame
        nebulaRec.x = nebFrame * nebulaRec.width;
        nebFrame++;
         
         /* 
            We need to reset the frame as soon as it gets larger than five, 
            since we have only frames 0 through five on the sprite sheet so 
            we can place an if check to see if frame is larger than 5, if yes
            we'll simply set it back to Zero.
          */

        if(nebFrame > 7) //  Position starts from 0 so we end up in 7, so eight is like in index 7.
        {
          nebFrame = 0;
        }
      }

       // Update Nebula 2 Running time
      neb2RunningTime += dT;
      if(neb2RunningTime>=nebUpdateTime)
      {
        neb2RunningTime = 0.0;
        // Update animation frame
        nebula2Rec.x = neb2Frame * nebula2Rec.width;
        neb2Frame++;
         
         /* 
            We need to reset the frame as soon as it gets larger than five, 
            since we have only frames 0 through five on the sprite sheet so 
            we can place an if check to see if frame is larger than 5, if yes
            we'll simply set it back to Zero.
          */

        if(neb2Frame > 7) //  Position starts from 0 so we end up in 7, so eight is like in index 7.
        {
          neb2Frame = 0;
        }
      }
      

      
      // Draw Nebula
      DrawTextureRec(nebula,nebulaRec, nebPos, WHITE);

      // Draw the Second Nebula
      DrawTextureRec(nebula,nebula2Rec,neb2Pos, RED);
    
      // Draw Scarfy
      DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
      
      // Finish/Stop Drawing
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
