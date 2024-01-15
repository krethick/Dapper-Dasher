#include "raylib.h"
int main()
{
    /*
     We keep the value to constant if we are not willing to change the value.
      -> We use the keyword const.

    Short hand for WindowShouldClose()!=true is !WindowShouldClose()
    */
    const int width{512};
    const int height{380};
    
    // Initialise the window and use this before while loop
    InitWindow(width,height,"Dapper Dasher");
    SetTargetFPS(60);
    
    // Keeping the WindowShouldClose as false.
    // Simple words negating the statement
    // We use the negation operator
    while(!WindowShouldClose())
    {
      // Start Drawing
      BeginDrawing();
      ClearBackground(WHITE);

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