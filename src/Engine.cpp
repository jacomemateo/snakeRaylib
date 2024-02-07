#include "Engine.h"

Engine::Engine(int screenWidth, int screenHeight, int gridSize)
    : screenWidth(screenWidth), screenHeight(screenHeight), gridSize(gridSize), max_score(0) {}

void Engine::init() {
    InitWindow(screenWidth, screenHeight, "Snake");
    SetTargetFPS(10);
    srand(time(nullptr));
}

void Engine::reset() {
    alive = true;
    currentDirection = Direction::DOWN;
    col_background = (Color){160, 190, 170, 255};
    xCells = screenWidth / gridSize;
    yCells = screenHeight / gridSize;

    std::vector<Snake> temp( startingLength,  Snake());
    snake = temp;
    snake[0].setPos(10, 1);
    foodX = 10;
    foodY = 10;
}

void Engine::exit() {
    CloseWindow();  // Close window and OpenGL context
}

KeyboardKey Engine::getKey() {
    return (KeyboardKey)GetKeyPressed();
}

void Engine::getInput(KeyboardKey input) {
    snake[0].updateLast();
    lastDirection = currentDirection;

    if(currentDirection == Direction::RIGHT && snake[0].getX() < xCells - 1) { snake[0].addX(1); }
    else if(currentDirection == Direction::LEFT && snake[0].getX() > 0) { snake[0].addX(-1); }
    else if(currentDirection == Direction::UP && snake[0].getY() > 0) { snake[0].addY(-1); }
    else if(currentDirection == Direction::DOWN && snake[0].getY() < yCells - 1) { snake[0].addY(1); }

    if (input == KEY_RIGHT && snake[0].getX() < xCells - 1 && lastDirection != Direction::LEFT) {
        currentDirection = Direction::RIGHT;
    }
    else if (input == KEY_LEFT && snake[0].getX() > 0 && lastDirection != Direction::RIGHT) {
        currentDirection = Direction::LEFT;
    }
    else if (input == KEY_UP && snake[0].getY() > 0 && lastDirection != Direction::DOWN) {
        currentDirection = Direction::UP;
    }
    else if (input == KEY_DOWN && snake[0].getY() < yCells - 1 && lastDirection != Direction::UP) {
        currentDirection = Direction::DOWN;
    }

    for(int i=1; i < snake.size(); i++) {
        snake[i].updateLast();
        snake[i].setPos(snake[i - 1].getLastX(), snake[i - 1].getLastY());
    }
}

void Engine::renderGridLines() {

    for(int i=0; i < screenWidth / gridSize; i++) {
        DrawLine(i * gridSize, 0, i * gridSize, screenHeight, col_gridLines);
    }

    for(int i=0; i < screenHeight / gridSize; i++) {
        DrawLine(0, i * gridSize, screenHeight, i * gridSize, col_gridLines);
    }
}


void Engine::renderSnake() {
    DrawRectangle( snake[0].getX() * gridSize + (gridSize - gridSize/1.3)/2 , snake[0].getY() * gridSize + (gridSize - gridSize/1.3)/2, gridSize/1.3, gridSize/1.3, col_snakeHead);

    for(int i=1; i < snake.size(); i++) {
        DrawRectangle( snake[i].getX() * gridSize + (gridSize - gridSize/1.3)/2 , snake[i].getY() * gridSize + (gridSize - gridSize/1.3)/2, gridSize/1.3, gridSize/1.3, col_snakeBody);
    }
}

void Engine::renderBorders() {
    DrawRectangle(0, 0 , gridSize, screenHeight, col_border);
    DrawRectangle(screenWidth-gridSize, 0 , gridSize, screenHeight, col_border);
    DrawRectangle(0, 0, screenWidth, gridSize, col_border);
    DrawRectangle(0, screenHeight-gridSize, screenWidth, gridSize, col_border);
}

void Engine::render() {
    BeginDrawing();
    ClearBackground(col_background);

    if(alive) {
        renderBorders();
        renderFood();
        renderSnake();
//        renderGridLines();
        std::string score_string = "Score: " + std::to_string(snake.size()-4) ;
        std::string max_scrore_string = "Max Score: " + std::to_string(max_score);

        DrawText(score_string.c_str(), gridSize, 0, gridSize,  WHITE);
        DrawText(max_scrore_string.c_str(), gridSize*8, 0, gridSize, WHITE);

    }
    else {
        reset();
        // DrawText("you die.", screenWidth / 2 - 100, screenHeight / 2, 40, WHITE);
    }

    EndDrawing();
}

bool Engine::isRunning() {
    return !WindowShouldClose();
}

std::tuple<int, int> Engine::generateFoodLocation() {
    int l_foodX = 1+(rand()%(xCells-2));
    int l_foodY = 1+(rand()%(yCells-2));

    return {l_foodX, l_foodY};
}

void Engine::renderFood() {
    if(snake[0].getX() == foodX && snake[0].getY() == foodY) {
        snake.emplace_back();

        std::tie(foodX, foodY) = generateFoodLocation();

        for(int i=0; i<snake.size(); i++) {
            if(foodX == snake[i].getX() || foodY == snake[i].getY()) {
                std::tie(foodX, foodY) = generateFoodLocation();
                i = 0;
            }
        }
    }

    DrawRectangle(foodX * gridSize, foodY * gridSize, gridSize, gridSize, col_food);
}

void Engine::death() {
    for(int i=1; i < snake.size(); i++) {
        if (snake[0].getX() == snake[i].getX() && snake[0].getY() == snake[i].getY()) {
            alive = false;
            if(snake.size() > max_score)
                max_score = snake.size()-4;
        }
    }
    if(snake[0].getX() == 0 || snake[0].getX() == xCells-1 || snake[0].getY() == 0 || snake[0].getY() == yCells-1) {
        alive = false;
        if(snake.size() > max_score)
            max_score = snake.size()-4;
    }
}
