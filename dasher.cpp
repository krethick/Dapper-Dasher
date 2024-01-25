/*
  
*/    

#include "raylib.h"
struct AnimData // Animation Data
{
  Rectangle rec;
  Vector2 pos;
  int frame;
  float updateTime;
  float runningTime;
};

int main()
{
    int windowDimensions[2];
    windowDimensions[0] = 512; // Width
    windowDimensions[1] = 380; // Height

    // Initialise the window and use this before while loop
    InitWindow(windowDimensions[0],windowDimensions[1],"Dapper Dasher");
    // Acceleration due to gravity (pixles/second)/second
    const int gravity {1'000}; 

    int velocity{0}; //Pixles per frame
    
    /*
      scarfy. => To access the inbuilt variables.
    */

   // Create a Nebula
   Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

   // AnimData for Nebula 
   AnimData nebData{ 
    {0.0, 0.0, nebula.width/8, nebula.height/8},  // Rectangle rec -> Stored together in one
    {windowDimensions[0], windowDimensions[1]-nebula.height/8}, // Vector2 pos  -> Stored togetherin one
    0,  // int frame
    1.0/12.0, // float updateTime
    0 // float runningTime
  };
    
    // AnimData for Nebula 2
    AnimData neb2Data{ 
    {0.0, 0.0, nebula.width/8, nebula.height/8},  // Rectangle rec
    {windowDimensions[0] + 300, windowDimensions[1]-nebula.height/8}, // Vector2 pos
    0,  // int frame
    1.0/16.0, // float updateTime
    0.0 // float runningTime
  };

   int nebVel{-200}; // Nebula Velocity
   
    // Compound datatype which has it's own variables, we use the dot . operator to access compund datatype
    // LoadTexture Takes the file path as an input parameter.
    // Scarfy Variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData; // Structure Data Type, we gave AnimData its own member variables.
    scarfyData.rec.width = scarfy.width/6;  // rec is from the struct AnimData
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0; 
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;
    
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
      if (scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height)
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
      nebData.pos.x += nebVel * dT; // We use dT to make it frame rate independent

      // Update Second Nebula Position
      neb2Data.pos.x += nebVel * dT; // We use dT to make it frame rate independent

      // Update Scarfy Position
      scarfyData.pos.y +=velocity * dT; // Update The pos y changes as adding with velocity.
      
      if(!isInAir) // !isInAir = Not in Air i.e !True = false 
      {
      // Update Running time
      scarfyData.runningTime += dT;
      if(scarfyData.runningTime>=scarfyData.updateTime) // We can even put this (isInAir==false) if we want.
      {
            scarfyData.runningTime = 0.0;
            
            // Update animation frame
            scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
            scarfyData.frame++; // Next time the frame will be increasing by 1
            
            /* 
            We need to reset the frame as soon as it gets larger than five, 
            since we have only frames 0 through five on the sprite sheet so 
            we can place an if check to see if frame is larger than 5, if yes
            we'll simply set it back to Zero.
          */
            if(scarfyData.frame>5) 
            {
              scarfyData.frame = 0;
            }
          }
      }
      
      // Update Nebula Running time
      
      nebData.runningTime += dT;
      if(nebData.runningTime>=nebData.updateTime)
      {
        nebData.runningTime = 0.0;
        
        // Update animation frame 
        nebData.rec.x = nebData.frame * nebData.rec.width;
        nebData.frame++;
        
         
         /* 
            We need to reset the frame as soon as it gets larger than five, 
            since we have only frames 0 through five on the sprite sheet so 
            we can place an if check to see if frame is larger than 5, if yes
            we'll simply set it back to Zero.
          */

        if(nebData.frame > 7) //  Position starts from 0 so we end up in 7, so eight is like in index 7.
        {
          nebData.frame = 0;
        }
      }

       // Update Nebula 2 Running time
      
      neb2Data.runningTime += dT;
      if(neb2Data.runningTime>=neb2Data.updateTime)
      {
        neb2Data.runningTime = 0.0;
        
        // Update animation frame
        neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
        neb2Data.frame++;
        
        /* 
            We need to reset the frame as soon as it gets larger than five, 
            since we have only frames 0 through five on the sprite sheet so 
            we can place an if check to see if frame is larger than 5, if yes
            we'll simply set it back to Zero.
          */

        if(neb2Data.frame > 7) //  Position starts from 0 so we end up in 7, so eight is like in index 7.
        {
          neb2Data.frame = 0;
        }
      }
      
      // Draw Nebula
      DrawTextureRec(nebula,nebData.rec, nebData.pos, WHITE);

      // Draw the Second Nebula
      DrawTextureRec(nebula,neb2Data.rec,neb2Data.pos, RED);
    
      // Draw Scarfy
      DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
      
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
