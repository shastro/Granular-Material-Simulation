// /*
//     Granular Simulation
//     Author:Skyler Hughes
//     Liscense: MIT
//     Goals:

//     - GUI ability to change to fullscreen
//     - Ability to add cube's, circles, and apply forces on them


// */

// #include "basic.hpp"
// #include "ball.hpp"
// #include "utils.hpp"
// #include "sim.hpp"

// int main(int argc, char **argv) {

//     // WINDOW SETUP //
//     sf::RenderWindow window(sf::VideoMode(1000, 1000), "Physics Simulation");

//     //Preload
//     enum MOUSE_STATE {RELEASED, CLICKED};

//     sf::Vector2f gravity_dir(0, -10);

//     //Engine Initialization
//     Simulation_Engine *Engine = new Simulation_Engine(50, 500, &window, HERTZ_DAMP);

//     // MAIN FRAMELOOP //
//     while (window.isOpen())
//     {
//         // EVENT POLLING //
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//             if (event.type == sf::Event::MouseButtonPressed)
//             {
//                 if (event.mouseButton.button == sf::Mouse::Left)
//                 {
//                     sf::Vector2f mousePos((float)event.mouseButton.x, (float)event.mouseButton.y);
//                     Engine->handleMouseEvent(mousePos);
//                 }
//             }
//             if(event.type == sf::Event::MouseButtonReleased)
//             {
//                 if (event.mouseButton.button == sf::Mouse::Left)
//                 {
//                     sf::Vector2f mousePos((float)event.mouseButton.x, (float)event.mouseButton.y);
//                     Engine->handleMouseEvent(mousePos);
//                 }
//             }
//             if (event.type == sf::Event::MouseMoved)
//             {
//                 sf::Vector2f mousePos((float)event.mouseButton.x, (float)event.mouseButton.y);

//             }
//         }

//         window.clear();
//         Engine->simLoop();
//         window.display();
        
//     }

//     return 0;
// }