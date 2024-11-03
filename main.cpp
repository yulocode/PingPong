#include <iostream>
#include <raylib.h>

#include <raylib.h>

class Paddle
{
public:
    int x, y;
    float width, heigth;
    int speed;
    void Draw()
    {
        DrawRectangle(x,y,width,heigth, WHITE);
    }
    void Update()
    {
        if(IsKeyDown(KEY_UP))
        {
            y = y - speed;
        } else if(IsKeyDown(KEY_DOWN))
        {
            y = y + speed;
        } 

        if(y <= 0)
        {
            y = 0;
        }
        if(y + heigth >= GetScreenHeight())
        {
            y = GetScreenHeight() - heigth;
        }
        
    }
};
Paddle player;
int width = 1260;
int heigth = 840;

Vector2 RectanglePOS2 = {width-35, 600};
Vector2 RectangleSize2 = {25.0f,120.0f};
class  Ball
{
public:
    float x,y;
    int speedX, speedY;
    float radius;

    void Draw()
    {
        DrawCircle(x,y,radius, WHITE);
    }
    void Update()
    {
        x += speedX;
        y += speedY;

         
        if(x + radius == player.width || x - radius <= 0)
        {
            speedX *= -1;
        }

        if(x + radius > GetScreenWidth())
        {
            
            DrawText("1", 10, 0, 25, WHITE);
            
        }

        if(x + radius == (RectanglePOS2.x && RectanglePOS2.y) )
        {
            speedX *= -1;
        }

        if(y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speedY *= -1;
        }
    }
};

//{width-35, heigth/2-60}
//{25.0f,120.0f}

Ball ball;
   
int main()
{
   

    InitWindow(width, heigth, "Ping Pong!");
    
    player.x = 10; 
    player.y = (heigth/2)-60;
    
    player.width = 25.0f;
    player.heigth = 120.0f;
    player.speed = 7;
    ball.x = width/2;   
    ball.y = heigth/2; 
    ball.radius = 20.0f; 
    ball.speedX = 7;
    ball.speedY = 7;

    while (!WindowShouldClose())
    {
        
        BeginDrawing();
            ClearBackground(GRAY);
            ball.Draw();
            ball.Update();
            player.Draw();
            player.Update();
    
            DrawRectangleV(RectanglePOS2, RectangleSize2, WHITE);

            DrawLine(width/2, 0, width/2,heigth, WHITE);

        EndDrawing();
    }
        
    CloseWindow();
    
    return 0;
}