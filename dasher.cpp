/*
  Looping Through the Hazards
  
  Eg:

  for (int i=0; i<3; i++)
   {
      nebulae[i].rec.x = 0.0;
      nebulae[i].rec.y = 0.0;
      nebulae[i].rec.width = nebula.width/8;
      nebulae[i].rec.height = nebula.height/8;
      nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
      nebulae[i].frame = 0;
      nebulae[i].runningTime = 0.0;
      nebulae[i].updateTime = 1.0/16.0;
   } 
   
   nebulae[0].pos.x = windowDimensions[0];
   nebulae[1].pos.x = windowDimensions[0] + 300;
   nebulae[2].pos.x = windowDimensions[0] + 600;

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

   // Creates an array size two that stores two anim data elements.
   // We use the braced initialisation.
   // Over here nebData will have index 0 and copies into the first element of the array.
   // and neb2Data will have index 1 and copies that into the second element.
   AnimData nebulae[3]{};

   for (int i=0; i<3; i++)
   {
      nebulae[i].rec.x = 0.0;
      nebulae[i].rec.y = 0.0;
      nebulae[i].rec.width = nebula.width/8;
      nebulae[i].rec.height = nebula.height/8;
      nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
      nebulae[i].frame = 0;
      nebulae[i].runningTime = 0.0;
      nebulae[i].updateTime = 1.0/16.0;
   } 
   
   nebulae[0].pos.x = windowDimensions[0];
   nebulae[1].pos.x = windowDimensions[0] + 300;
   nebulae[2].pos.x = windowDimensions[0] + 600;

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
      nebulae[0].pos.x += nebVel * dT; // We use dT to make it frame rate independent

      // Update Second Nebula Position
      nebulae[1].pos.x += nebVel * dT; // We use dT to make it frame rate independent

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
      nebulae[0].runningTime += dT;
      if(nebulae[0].runningTime>=nebulae[0].updateTime)
      {
        nebulae[0].runningTime = 0.0;
        
        // Update animation frame 
        nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
        nebulae[0].frame++;
        
         
         /* 
            We need to reset the frame as soon as it gets larger than five, 
            since we have only frames 0 through five on the sprite sheet so 
            we can place an if check to see if frame is larger than 5, if yes
            we'll simply set it back to Zero.
          */

        if(nebulae[0].frame > 7) //  Position starts from 0 so we end up in 7, so eight is like in index 7.
        {
          nebulae[0].frame = 0;
        }
      }

       // Update Nebula 2 Running time
      
      nebulae[1].runningTime += dT;
      if(nebulae[1].runningTime>=nebulae[1].updateTime)
      {
        nebulae[1].runningTime = 0.0;
        
        // Update animation frame
       nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
       nebulae[1].frame++;
        
        /* 
            We need to reset the frame as soon as it gets larger than five, 
            since we have only frames 0 through five on the sprite sheet so 
            we can place an if check to see if frame is larger than 5, if yes
            we'll simply set it back to Zero.
          */

        if(nebulae[1].frame > 7) //  Position starts from 0 so we end up in 7, so eight is like in index 7.
        {
          nebulae[1].frame = 0;
        }
      }
      
      // Draw Nebula
      DrawTextureRec(nebula,nebulae[0].rec, nebulae[0].pos, WHITE);

      // Draw the Second Nebula
      DrawTextureRec(nebula,nebulae[1].rec,nebulae[1].pos, RED);
    
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
