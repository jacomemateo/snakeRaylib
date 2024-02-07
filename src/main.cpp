#include "Engine.h"

int main(void)
{
    /* Initialization */
    Engine engine(600, 600, 30);
    engine.init();
    engine.reset();

    /* Main game loop */
    while (engine.isRunning()) {
        /* Update Stuff */
        engine.death(); // See if player is still alive
        engine.getInput(Engine::getKey()); // Get input

        // Render
        engine.render();
    }

    engine.exit();
    return 0;
}
