/*
 Functions
   To Declare Functions we need:
      *  Return Type
      *  Function Name
      *  Input Parameters
      *  Function body 
      *  Return Statements 
 Example:
   
   int addInts(int a, int b)
   {
     return a + b;
   }

   int result = addInts(2,3);

   addInts => Function Name
  (int a, int b) => Input Parameters
   
   {             =>
     return a+b; =>   Function Body
   }             =>

   return => It is the return Statement 

   int result = addInts(2,3);
    => The two gets copied to int a
    => The three gets copied to int b
    => The final result will a + b; i.e 2+3 = 5

  Another Example:
  
    int addInts(int a, int b)
   {
     return a + b;
   }
   
   int two{2};  // Using curly braces to initialize a variable also prevents narrowing
   int three{3};
   int result = addInts(two,three);
    Output will be 5;

  What is narrowing ?
   =>  Narrowing, or more precisely narrowing conversion, is the implicit conversion 
       of arithmetic values that includes​ a loss of accuracy.

 Note : A function that has no return values is called a void function
        and the return type is void.
  
  Void Function :
     * void for no return type
     * Does not need the return keyword
  
  Eg:
    1) void sayHi() 
       {
       printf("Hi!");
       }

    2) void makeTwo(int a) 1
       { 
         a = 2;
       }

       int three{3};
       makeTwo(three);   

         [a]  [three]
          2     3

      * Now this function seems to change the input parameter, but the
        truth is input parameter to functions are local to the function.
      
      * Inside the function the input parameter called A takes three as copy,
        so A starts off with a value of three in the function body, but quickly
        becomes two as we use the assignment operator to assign a value of two.

      * After 1 line the end of the function body is reached and the function has
        finished. 

      * But after the function has finished, the integer called three still remains
        unchanged and that's because three is passed in to make two and the input 
        parameter A gets the value of three as a copy

      * So functions do not alter the values of variables outside the function.
      
      * They simple take those values in as copied and perform any actions specified
        inside the function body.
      
     

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
   
   const int sizeOfNebulae{10}; // Create the size of nebulaes
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
     
      
      for (int i=0; i<sizeOfNebulae; i++)
      {
        // Update Position of each nebula
       nebulae[i].pos.x += nebVel * dT; // We use dT to make it frame rate independent
      }
      
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
      
      // Create a for loop for creating Nebulaes

      for (int i=0; i<sizeOfNebulae; i++)
      {
          // Update Nebula Running time
         nebulae[i].runningTime += dT;
         if(nebulae[i].runningTime>=nebulae[i].updateTime)
         {
            nebulae[i].runningTime = 0.0;
            // Update animation frame 
            nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
            nebulae[i].frame++;
            /* 
             We need to reset the frame as soon as it gets larger than five, 
             since we have only frames 0 through five on the sprite sheet so 
             we can place an if check to see if frame is larger than 5, if yes
             we'll simply set it back to Zero.
            */
            if(nebulae[i].frame > 7) //  Position starts from 0 so we end up in 7, so eight is like in index 7.
            {
              nebulae[i].frame = 0;
            }
          }
       }
     
      for(int i=0; i<sizeOfNebulae; i++)
      {
       // Draw multiple Nebulas here
      DrawTextureRec(nebula,nebulae[i].rec, nebulae[i].pos, WHITE);
      }
      
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
