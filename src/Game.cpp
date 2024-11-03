#include <iostream>
#include <raylib.h>

class Paddle
{

protected:
    void LimitedMoviment()
    {   
        if(y <= 0)
        {
            y = 0;
        }
        if(y + heigth >= GetScreenHeight())
        {
            y = GetScreenHeight() - heigth;
        }
    }
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

        LimitedMoviment();
    }
};

class CpuPaddle: public Paddle
{
    public:
    void Update(int ballY)
    {
        if(y + heigth/2 > ballY)
        {
            y = y - speed;
        }

        if(y + heigth/2 <= ballY)
        {
            y = y + speed;
        }

        LimitedMoviment();
    }
};
Paddle player;
int width = 1260;
int heigth = 840;

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

        if(y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speedY *= -1;
        }
        if(y + radius >= GetScreenWidth() || y - radius <= 0)
        {
            speedX *= -1;
        }
    }
};

//{width-35, heigth/2-60}
//{25.0f,120.0f}

Ball ball;
CpuPaddle cpupaddle; 
   
int main()
{
   

    InitWindow(width, heigth, "Ping Pong!");
    cpupaddle.x = width-35;
    cpupaddle.y = (heigth/2)-60; 
    cpupaddle.width = 25.0f;
    cpupaddle.heigth = 120.0f;
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

    bool isMenu = true;
    while (!WindowShouldClose())
    {
        DrawText("Press Enter",width/2, heigth/2, 50, BLACK);
        if(IsKeyPressed(KEY_ENTER))
        {
            isMenu = false;
        }
        
        BeginDrawing();
            ClearBackground(GRAY);
            ball.Draw();
            ball.Update();
           
            player.Draw();
            player.Update();

            cpupaddle.Draw();
            cpupaddle.Update(ball.y);
            DrawLine(width/2, 0, width/2,heigth, WHITE);

        EndDrawing();
    }
        
    CloseWindow();
    
    return 0;
}