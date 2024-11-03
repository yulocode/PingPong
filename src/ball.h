#include <raylib.h>
class Ball
{
public:
    float x,y;
    int speedX, speedY;
    float radius;
    void Draw();
    void Update();
};