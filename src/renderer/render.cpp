#include "render.hpp"
void updateParticles(int frame, std::vector<Particle*>& particles, rj::Document& data)
{
    
    for (int j = 0; j < data["PARTICLE_COUNT"].GetInt(); j++) {

        struct p_data_t p_data;

        sf::Vector2f pos(0,0);
        sf::Vector2f vel(0,0);
        sf::Vector2f acc(0,0);
        // Value Capture for shorthand
        rj::Value& posX = data["FRAME_DATA"][frame]["SUBFRAMES"][0]["particles"][j]["p_data"]["p"]["x"];
        rj::Value& posY = data["FRAME_DATA"][frame]["SUBFRAMES"][0]["particles"][j]["p_data"]["p"]["y"];
        rj::Value& velX = data["FRAME_DATA"][frame]["SUBFRAMES"][0]["particles"][j]["p_data"]["v"]["x"];
        rj::Value& velY = data["FRAME_DATA"][frame]["SUBFRAMES"][0]["particles"][j]["p_data"]["v"]["y"];
        rj::Value& accX = data["FRAME_DATA"][frame]["SUBFRAMES"][0]["particles"][j]["p_data"]["a"]["x"];
        rj::Value& accY = data["FRAME_DATA"][frame]["SUBFRAMES"][0]["particles"][j]["p_data"]["a"]["y"];
        rj::Value& velmag = data["FRAME_DATA"][frame]["SUBFRAMES"][0]["particles"][j]["p_data"]["v_mag"];

        double v_mag = 0.0f;
        if (!posX.IsNull() | !posY.IsNull() ) {
            p_data.pos.x = posX.GetDouble();
            p_data.pos.y = posY.GetDouble();
        } else {
            p_data.pos.x = -1000;
            p_data.pos.y = -1000;
        }


        if (!velX.IsNull() | !velY.IsNull() ) {
            p_data.vel.x = velX.GetDouble();
            p_data.vel.y = velY.GetDouble();
        } else {
            p_data.vel.x = 0;
            p_data.vel.y = 0;
        }

        if (!accX.IsNull() | !accY.IsNull() ) {
            p_data.acc.x = accX.GetDouble();
            p_data.acc.y = accY.GetDouble();
        } else {
            p_data.acc.x = 0;
            p_data.acc.y = 0;
        }

        if ( !velmag.IsNull() ) {
            p_data.v_mag = velmag.GetDouble();
        }

        particles.at(j)->updateData(p_data);
    }

}