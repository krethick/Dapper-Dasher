/*
  Winning and Losing
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

// Function to check if scarfy is on the ground or on the air
bool isOnGround(AnimData data, int windowHeight)
{
   return data.pos.y >= windowHeight - data.rec.height;
}

// Function to update running time of scarfy and nebulae
AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    // Update Running Time 
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    {
      data.runningTime = 0.0;
      // update animation frame
      data.rec.x = data.frame * data.rec.width;
      data.frame++;
      if (data.frame > maxFrame)
      {
          data.frame = 0;
      } 
    }
    return data;
}



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
   
   const int sizeOfNebulae{3}; // Create the size of nebulaes
   // Creates an array size two that stores two anim data elements.
   // We use the braced initialisation.
   // Over here nebData will have index 0 and copies into the first element of the array.
   // and neb2Data will have index 1 and copies that into the second element.
   AnimData nebulae[sizeOfNebulae]{};

   for (int i=0; i<sizeOfNebulae; i++)
   {
      nebulae[i].rec.x = 0.0;
      nebulae[i].rec.y = 0.0;
      nebulae[i].rec.width = nebula.width/8;
      nebulae[i].rec.height = nebula.height/8;
      nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
      nebulae[i].frame = 0;
      nebulae[i].runningTime = 0.0;
      nebulae[i].updateTime = 1.0/16.0;
      nebulae[i].pos.x = windowDimensions[0] + i * 300; // This a another way in the loop
   }  

   float finishLine { nebulae[sizeOfNebulae - 1].pos.x}; // Created and Initialised the Finish Line

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
    

      // Load the background texture
    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{}; // Automaticlly initialises the value to 0.
    
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float mgX{}; // Automaticlly initialises the value to 0.

    Texture2D foreground = LoadTexture("textures/foreground.png");
    float fgX{}; // Automaticlly initialises the value to 0.

    bool collision{}; // By blank meaning we have initialised it to false

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

      bgX -= 20 * dT; // Image move towards the left and scrolled at 20 pixles/sec (like a care moving in reverse)
      mgX -= 40 * dT;
      fgX -= 80 * dT;
      if (bgX <= -background.width*2)
      {
         bgX = 0.0;
      }
      
      if(mgX <= -midground.width*2)
      {
         mgX = 0.0;
      }

      if(fgX <= -foreground.width*2)
      {
         fgX = 0.0;
      }

      // Draw the background
      Vector2 bg1Pos{bgX, 0.0};
      DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE); // rotation is the 3rd one and the 4th one is the scale.
      Vector2 bg2Pos{bgX + background.width * 2, 0.0}; // For duplication we use (bgX + background.width * 2) background.width * 2 because we are matching up with scale 2.
      DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE); // rotation is the 3rd one and the 4th one is the scale.
      
      // Draw the midground
      Vector2 mg1Pos{mgX, 0.0};
      DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE); // rotation is the 3rd one and the 4th one is the scale.
      Vector2 mg2Pos{mgX + midground.width * 2, 0.0}; // For duplication we use (mgX  + midground.width * 2) midground.width * 2 because we are matching up with scale 2.
      DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE); // rotation is the 3rd one and the 4th one is the scale.

      // Draw the foreground
      Vector2 fg1Pos{fgX, 0.0};
      DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE); // rotation is the 3rd one and the 4th one is the scale.
      Vector2 fg2Pos{fgX + foreground.width * 2, 0.0}; // For duplication we use (mgX  + foreground.width * 2) foreground.width * 2 because we are matching up with scale 2.
      DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE); // rotation is the 3rd one and the 4th one is the scale.

      
      // Perform ground check
      if (isOnGround(scarfyData,windowDimensions[1]))
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
     
      
      for (int i=0; i<sizeOfNebulae; i++)
      {
        // Update Position of each nebula
       nebulae[i].pos.x += nebVel * dT; // We use dT to make it frame rate independent
      }
      
      // Update Scarfy Position
      scarfyData.pos.y +=velocity * dT; // Update The pos y changes as adding with velocity.
      
      if(!isInAir) // !isInAir = Not in Air i.e !True = false 
      {
         scarfyData = updateAnimData(scarfyData, dT, 5);
      }
      
      // Create a for loop for creating Nebulaes

      for (int i=0; i<sizeOfNebulae; i++)
      {
         nebulae[i] = updateAnimData(nebulae[i], dT, 7);
      }

      // For collision
      for(AnimData nebula : nebulae)
      {
        float pad{50}; // We use this because to reduce the sprite size so collision take place when the object hits not the object boundaries
         
         Rectangle nebRec{
          nebula.pos.x + pad,
          nebula.pos.y + pad,
          nebula.rec.width - 2 * pad,  // Reduce the sprite boundary size
          nebula.rec.height - 2 * pad
         };

         Rectangle scarfyRec {
          scarfyData.pos.x,
          scarfyData.pos.y,
          scarfyData.rec.width,
          scarfyData.rec.height
         };

         if(CheckCollisionRecs(nebRec, scarfyRec))
         {
           collision = true;
         }
      }

         if(collision)
         {
           // Lose the game
           DrawText("GAME OVER", windowDimensions[0]/4, windowDimensions[1]/2, 40, RED);
         }
         else if(scarfyData.pos.x>=finishLine)
         {
           // Win the Game
           DrawText("YOU WIN", windowDimensions[0]/4, windowDimensions[1]/2, 40, GREEN);
         }
          else
         {
            for(int i=0; i<sizeOfNebulae; i++)
            {
            // Draw multiple Nebulas here
             DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
            }
            // Draw Scarfy
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
         }

        
      
    // Update Finish line
     finishLine += nebVel * dT;

      
      
      // Draw Background
      
      
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
   UnloadTexture(background); // Unload texture background
   UnloadTexture(midground); // Unload texture midground
   UnloadTexture(foreground); // Unload texture foreground
   CloseWindow();
}
