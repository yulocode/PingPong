#include <raylib.h>

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

         
        if(x + radius >= GetScreenWidth() || x - radius <= 0)
        {
            speedX *= -1;
        }

        if(y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speedY *= -1;
        }
    }
};