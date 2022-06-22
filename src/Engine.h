#ifndef SNAKE_ENGINE_H
#define SNAKE_ENGINE_H
#include "raylib.h"
#include "Snake.h"
#include <cstdlib>
#include <vector>
#include <iostream>

class Engine {
private:
    enum class Direction {
        UP = 0,
        DOWN,
        LEFT,
        RIGHT
    };


    /* Color */
    const Color col_snakeHead = (Color){35, 45, 40, 255};
    const Color col_snakeBody = (Color){60, 75, 65, 255 };
    const Color col_gridLines = BLACK;
    const Color col_border = (Color){60, 75, 65, 255 };
    const Color col_food = (Color){200, 90, 80, 255};
    Color col_background = (Color){160, 190, 170, 255};

    /* Window Stuff */
    int screenWidth, screenHeight;
    int gridSize; // Size of each cell, in pixels
    int xCells{}, yCells{}; // Number of cells in snake

    /* Snake Stuff */
    const int startingLength = 4;
    std::vector<Snake> snake;
    Direction currentDirection = Direction::RIGHT;
    Direction lastDirection = currentDirection;
    bool alive = true; // Determines if player is alive

    /* Food Stuff */
    int foodX{}, foodY{};

public:
    Engine(int screenWidth, int screenHeight, int gridSize);
    void init();
    static void exit();
    bool isRunning();

    /* Logic functions */
    void getInput(KeyboardKey input);
    static KeyboardKey getKey();

    /* Render Functions */
    void render(); // Main render function
    void renderGridLines();
    void renderSnake();
    void renderBorders();
    void renderFood();

    /* Check for death  */
    void death();
};


#endif //SNAKE_ENGINE_H
