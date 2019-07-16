#include "draw.hpp"
#include "particle.hpp"
#include "utils.hpp"
#include "render.hpp"
#include <ctime>
#include "unistd.h"
// /*
//     Granular Simulation
//     Author:Skyler Hughes
//     Liscense: MIT


// */

sf::Event event;

int main(int argc, char**argv) {

    std::string filename;

    if(argc == 1){
        printf("Enter filename: ");
        std::cin >> filename;
    }else{
        filename = std::string(argv[1]);
    }


    std::string data_path = "../sim_data/";

    // CONFIG PARSING //

    const char *data_json = load_file((data_path + filename).c_str());

    rj::Document data;
    PRINT("PARSING DATA")
    data.Parse(data_json);
    PRINT("PARSING COMPLETE")

    free((void *)data_json);


    int FRAMECOUNT = data["FRAMELIMIT"].GetInt();

    // WINDOW SETUP //
    sf::RenderWindow window(sf::VideoMode(data["WINDOW_DATA"]["width"].GetInt(), data["WINDOW_DATA"]["height"].GetInt()),
                            (std::string("Rendering Sim: ") + filename).c_str());

    std::vector<Particle*> particles;

    PRINT("INITIALIZING PARTICLES")
    // Particle Initialization with first frame's data
    for (int j = 0; j < data["PARTICLE_COUNT"].GetInt(); j++) {


        sf::Vector2f pos(0, 0);
        sf::Vector2f vel(0, 0);
        sf::Vector2f acc(0, 0);
        // Value Capture for shorthand
        rj::Value& posX = data["FRAME_DATA"][0]["SUBFRAMES"][0]["particles"][j]["p_data"]["p"]["x"];
        rj::Value& posY = data["FRAME_DATA"][0]["SUBFRAMES"][0]["particles"][j]["p_data"]["p"]["y"];
        rj::Value& velX = data["FRAME_DATA"][0]["SUBFRAMES"][0]["particles"][j]["p_data"]["v"]["x"];
        rj::Value& velY = data["FRAME_DATA"][0]["SUBFRAMES"][0]["particles"][j]["p_data"]["v"]["y"];
        rj::Value& accX = data["FRAME_DATA"][0]["SUBFRAMES"][0]["particles"][j]["p_data"]["a"]["x"];
        rj::Value& accY = data["FRAME_DATA"][0]["SUBFRAMES"][0]["particles"][j]["p_data"]["a"]["y"];
        rj::Value& velmag = data["FRAME_DATA"][0]["SUBFRAMES"][0]["particles"][j]["p_data"]["v_mag"];
        double v_mag = 0.0f;

        if (!posX.IsNull() | !posY.IsNull() ) {
            pos.x = posX.GetDouble();
            pos.y = posY.GetDouble();
        } else {
            pos.x = 0;
            pos.y = 0;
        }


        if (!velX.IsNull() | !velY.IsNull() ) {
            vel.x = velX.GetDouble();
            vel.y = velY.GetDouble();
        } else {
            vel.x = 0;
            vel.y = 0;
        }

        if (!accX.IsNull() | !accY.IsNull() ) {
            acc.x = accX.GetDouble();
            acc.y = accY.GetDouble();
        } else {
            acc.x = 0;
            acc.y = 0;
        }
        if ( !velmag.IsNull() ) {
            v_mag = velmag.GetDouble();
        }
        int radius = data["FRAME_DATA"][0]["SUBFRAMES"][0]["particles"][j]["p_data"]["r"].GetInt();
        int id     = data["FRAME_DATA"][0]["SUBFRAMES"][0]["particles"][j]["id"].GetInt();

        Particle *p = new Particle(pos, vel, acc, radius, id, v_mag, &window);
        particles.emplace_back(p);
    }

    // Setting Up Text //

    sf::Font font;
    if(!font.loadFromFile("../assets/font.ttc")){
        PRINT("\e[91;50m[ERROR]: Font not found!\e[37m")
    }

    // Framecount
    sf::Text t_frameCount;
    t_frameCount.setFont(font);
    t_frameCount.setPosition(sf::Vector2f(0.0, 30));
    t_frameCount.setColor(sf::Color::Red);
    t_frameCount.setCharacterSize(24);
    
    // Sim Name
    sf::Text t_simname;
    t_simname.setFont(font);
    std::string sim("sim: ");
    t_simname.setString((sim + filename).c_str());
    t_simname.setColor(sf::Color::Blue);
    t_simname.setCharacterSize(24);
   PRINT("\e[32mINITIALIZATION COMPLETE\e[37m")


    // MAIN FRAMELOOP //

    PRINT("BEGINING MAIN LOOP")
    int FRAMERATE = 60;
    for (int i = 0; i < data["FRAMELIMIT"].GetInt(); i++)
    {
        // EVENT POLLING //
        sf::Event event;

        clock_t start, end;
        start = clock();
        window.clear(sf::Color(250,250,250));

        for (auto & particle : particles) {
            particle->draw();
        }
        updateParticles(i, particles, data);


        std::string s("frame: ");
        s =  s + std::to_string(i);
        t_frameCount.setString(s.c_str());

        window.draw(t_simname);
        window.draw(t_frameCount);


        window.display();
        end = clock();

        // DRAWING TEXT //


        double time = ((double)(end - start) / (double)CLOCKS_PER_SEC) * 1000000;
        double refresh_rate = ((double)1     / (double)FRAMERATE)      * 1000000;
        // FRAMERATE MANAGEMENT //
        double remainder;
        if (refresh_rate - time > 0) {

            remainder = refresh_rate - time; // In micro-seconds
        } else {
            remainder = 0;
        }
        usleep(remainder);

       LOG("FRAME: ", i)

        

        window.pollEvent(event);
        
        if (event.type == sf::Event::Closed) {
            window.close();
            return 0;
        }
    }

    PRINT("FINISHED")
    sf::Event newevent;
    while (1) {

        

        window.pollEvent(newevent);

        if (newevent.type == sf::Event::Closed) {
            window.close();
            return 0;
        }
        
        
    }

    return 0;

}