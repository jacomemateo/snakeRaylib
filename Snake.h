#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H
#include "raylib.h"

class Snake {
private:
    int xPos, yPos; // Coordinates in snake
    int last_xPos, last_yPos; // Previous coordinates

public:
    Snake() {
        xPos = 0;
        yPos = 0;
        last_xPos = xPos;
        last_yPos = yPos;
    };

    int getX() const { return xPos; }
    int getY() { return yPos; }
    void addX(int x) { xPos += x; }
    void addY(int y) { yPos += y; }
    void setPos(int x, int y) {
        xPos = x;
        yPos = y;
    }

    void updateLast() { // Updates the last coordinates
        last_xPos = xPos;
        last_yPos = yPos;
    }
    int getLastX () { return last_xPos; }
    int getLastY() { return last_yPos; }

};


#endif //SNAKE_SNAKE_H
