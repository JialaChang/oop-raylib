#include "raylib.h"
#include "bubble.h"
#include <iostream>
#include <vector>

std::vector<Bubble> bubbles;

void generateBubble() {
    int colorType = GetRandomValue(0, 2);
    if (colorType == 0) {
        bubbles.push_back(Bubble(GetRandomValue(50, 1850), GetRandomValue(800, 1000), 70, RED, 5.0f, -10));
    } 
    else if (colorType == 1) {
        bubbles.push_back(Bubble(GetRandomValue(50, 1850), GetRandomValue(800, 1000), 20, GOLD, 10.0f, 20));
    } 
    else {
        bubbles.push_back(Bubble(GetRandomValue(50, 1850), GetRandomValue(800, 1000), 50, PURPLE, 6.5f, 5));
    }
}

int main() {

    InitWindow(1920, 1080, "Raylib OOP");
    InitAudioDevice();
    Sound popSound = LoadSound("./resources/pop1.wav");
    SetTargetFPS(60);
    Music bgm = LoadMusicStream("./resources/bgm.mp3");
    PlayMusicStream(bgm);

    int score = 0;
    float timeLeft = 50.0f;
    bool gameOver = false;
    // create object
    for (int i = 0; i < 20; i++) {
        generateBubble();
    }

    while (!WindowShouldClose()) {
        UpdateMusicStream(bgm);
        // if game end
        if (!gameOver) {
            timeLeft -= GetFrameTime();
            if (timeLeft <= 0) {
                timeLeft = 0;
                gameOver = true;
                StopMusicStream(bgm);
            }

            // check if mouse click bubbles
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                float mouseX = float(GetMouseX());
                float mouseY = float(GetMouseY());

                for (int i = 0; i < bubbles.size(); ++i) {
                    if (bubbles[i].checkClick(mouseX, mouseY)) {
                        PlaySound(popSound);
                        score += bubbles[i].getPoint();
                        bubbles.erase(bubbles.begin() + i);
                        generateBubble();
                    }
                }
            }
            for (auto &b : bubbles) b.updatePos();
        }
        
        BeginDrawing();

        ClearBackground(RAYWHITE);
        if (!gameOver) {
            for (auto &b : bubbles) b.draw();
            DrawText("Score:", 20, 20, 20, GRAY);
            DrawText(TextFormat("%d", score), 100, 20, 20, BLACK);
            DrawText("Time:", 20, 50, 20, GRAY);
            DrawText(TextFormat("%.1f", timeLeft), 100, 50, 20, BLACK);
            DrawText("Original music", 1700, 1000, 20, GRAY);
        }
        else {
            DrawText("Score:", 840, 100, 40, GRAY);
            DrawText(TextFormat("%d", score), 1000, 100, 40, BLACK);
            DrawText("Time's up", 760, 500, 100, RED);
            DrawText("Original music", 1700, 1000, 20, GRAY);
        }
        

        EndDrawing();
    }

    UnloadSound(popSound);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
