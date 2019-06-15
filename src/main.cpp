#include "basic.hpp"
#include "ball.hpp"
#include "utils.hpp"
#include "sim.hpp"

#define TIME_DELTA 0.1 //ms

int main(int argc, char **argv) {


    /*
        Goals:

        - GUI ability to change to fullscreen
        - Ability to add cube's, circles, and apply forces on them


    */

    //Preload




    // WINDOW SETUP //
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Physics Simulation");

    //Engine Initialization
    Simulation_Engine *Engine = new Simulation_Engine(10, 50, &window);

    // MAIN FRAMELOOP //
    while (window.isOpen())
    {
        // EVENT POLLING //
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        //MAIN LOGIC//
        Engine->detectCollisions();
        Engine->calcSteps();
        Engine->drawElements();




        
        window.display();
    }






    return 0;
}