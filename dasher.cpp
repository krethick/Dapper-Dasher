#include "raylib.h"
int main()
{
    /*
      SPRITE SHEET AND ANIMATION
       What is a sprite?
         * It is an 2D Image, that gets drawn to a screen in a game.
         * It also has transparent backgrounds
         * Each pixel has a color value 
           -> Red
           -> Green
           -> Blue
           -> Alpha
         * It is a one single image but contains a multiple images in a single file
         * It saves memory and it also allows us to load a single file rather than several individual images
         * For eg in a particular frame we may be drawing one piece of the sprite sheet
           and if we want to update the animation, we draw the next piece till the last one.
           and we would start all over again.

           DrawTextureRec(texture, source, position, tint);
            * Basically taking the rectangle from the sprite sheet.
            * Takes four input parameters
               i)  Texture is the sprite sheet image.
               ii) Source is the section of the sprite sheet.
               iii) Position which is located on the window.
               iv) Tint is a color

            Steps:-
            i) Texture - Load the scarfy texture
           ii) Source  - It is a rectangle where provide to specify which part of the sprite
                         sheet we want to draw.
             Rectangle has its own set of properties like 
                   * x, y, width and height
              
              Eg of a sprite where 
                x = 0 
                -> incase if you want the next scarfing image, this means the x of our rectangle needs
                   to be updated (w/6) or (w/6,0)
                y = 0
            width = w/6 i.e spritesheet has 6 images.
           height = h

          iii) Position - Location in the window
          iv)  tint - color to tint the sprite (WHITE)
      
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

    // Compound datatype which has it's own variables, we use the dot . operator to access compund datatype
    // LoadTexture Takes the file path as an input parameter.
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec; // Texture rec needs an rectangle describing which section of the sprite sheet to draw.
    Vector2 scarfyPos; // For the position 
    
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
      if (posY >= Window_Height - height)
      {
        // Rectangle on the ground
        velocity = 0;
        // Create a variable for in the air
        isInAir = false;
      }
      else
      {
        // Rectangle on the air
         velocity += gravity;
         isInAir = true;
      }

      // Jump Check
      if(IsKeyPressed(KEY_SPACE) && !isInAir) // !isInAir meaning not in Air.
      {
        velocity +=jumpVel; // It jumps to jumpvel value
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