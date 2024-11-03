#include <iostream>
#include <raylib.h>

class Paddle
{
protected:
    void LimitedMoviment()
    {
        if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }

public:
    float x, y;
    float width, height;
    int speed;

    void Draw()
    {
        DrawRectangle(x, y, width, height, WHITE);
    }

    void Update()
    {
        if (IsKeyDown(KEY_UP))
        {
            y -= speed;
        }
        else if (IsKeyDown(KEY_DOWN))
        {
            y += speed;
        }

        LimitedMoviment();
    }
};

class CpuPaddle : public Paddle
{
public:
    void Update(float ballY)
    {
        if (y + height / 2 < ballY)
        {
            y += speed; // Move para baixo
        }
        else if (y + height / 2 > ballY)
        {
            y -= speed; // Move para cima
        }

        LimitedMoviment(); // Garante que o paddle fique dentro da tela
    }
};

Paddle player;
int width = 1260;
int height = 840;

class Ball
{
public:
    float x, y;
    int speedX, speedY;
    float radius;

    void Draw()
    {
        DrawCircle(x, y, radius, WHITE);
    }

    void Update(int &score)
    {
        x += speedX;
        y += speedY;

        if (x + radius > GetScreenWidth())
        {
            // Ponto marcado para o jogador
            score++;
            Reset();
        }
        if (x + radius < 0)
        {
            // Ponto marcado para o CPU
            score--;
            Reset();
        }

        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speedY *= -1;
        }
    }

    void Reset()
    {
        x = width / 2;
        y = height / 2;
        speedX = (speedX < 0 ? -7 : 7); // Mantém a direção original, muda apenas a posição
        speedY = 7; // Reseta a velocidade vertical
    }
};

Ball ball;
CpuPaddle cpu;

int main()
{
    InitWindow(width, height, "Ping Pong!");
    cpu.x = width - 35;
    cpu.y = (height / 2) - 60;
    cpu.width = 25.0f;
    cpu.height = 120.0f;
    cpu.speed = 10;

    player.x = 10;
    player.y = (height / 2) - 60;
    player.width = 25.0f;
    player.height = 120.0f;
    player.speed = 7;

    ball.x = width / 2;
    ball.y = height / 2;
    ball.radius = 20.0f;
    ball.speedX = 7;
    ball.speedY = 7;

    int score = 0; // Variável para armazenar o score
    bool isInMenu = true;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            isInMenu = false;
        }
        else if (IsKeyPressed(KEY_P))
        {
            isInMenu = true;
        }

        BeginDrawing();

        if (isInMenu)
        {
            ClearBackground(RAYWHITE);
            DrawText("Press enter to play", 190, 200, 50, BLACK);
            DrawText("Controls: Up and Down", 190, 250, 20, BLACK);
            DrawText("Press P to pause", 190, 270, 20, BLACK);
        }
        else
        {
            ClearBackground(GRAY);
            ball.Draw();
            ball.Update(score); // Passa o score para a função Update da bola

            if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.x, player.y, player.height, player.width }))
            {
                ball.speedX *= -1;
                ball.x = player.x - ball.radius;
            }
            if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ cpu.x, cpu.y, cpu.height, cpu.width }))
            {
                ball.speedX *= -1;
                ball.x = cpu.x - ball.radius;
            }

            player.Draw();
            player.Update();

            cpu.Draw();
            cpu.Update(ball.y);
            DrawLine(width / 2, 0, width / 2, height, WHITE);

            // Desenha o score na tela
            DrawText(TextFormat("Score: %i", score), 10, 10, 20, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
