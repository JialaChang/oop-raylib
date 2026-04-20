#ifndef BUBBLE_H
#define BUBBLE_H

#include "raylib.h"

class Bubble {
private:
    float posX;
    float posY;
    float radius;
    Color color;
    float speed;
    int point;
    bool invis;

public:
    // constructor
    Bubble(float x, float y, float r, Color c, float s, int p):
        posX(x), posY(y), radius(r), color(c), speed(s), point(p), invis(false) {
    }

    int getPoint() {return point;}

    // draw bubble
    void draw() {
        DrawCircle(posX, posY, radius, color);
    }

    // check mouse click
    bool checkClick(float mouseX, float mouseY) {
        float dx = mouseX - posX;
        float dy = mouseY - posY;
        float distSqur = (dx * dx) + (dy * dy);
        float radiSqur = radius * radius;
        if (distSqur <= radiSqur) {
            return true;
        }
        return false;
    }

    // let bubble move upward
    void updatePos() {
        posY -= speed;
        if ((posY - radius) < 0) {
            posY = 1000 + radius;
            posX = GetRandomValue(100, 1800);
        } 
    }
};

#endif