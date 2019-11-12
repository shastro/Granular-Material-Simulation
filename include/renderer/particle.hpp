#ifndef PARTICLE_H
#define PARTICLE_H
#include "draw.hpp"
#include "utils.hpp"

/** Class to handle rendering of particle data, represents something draw able.
*/
class Particle{

private:
    //Kinematic Data
    sf::Vector2f m_pos; //Position
    sf::Vector2f m_vel; //Velocity
    sf::Vector2f m_acc; //Acceleration
    float m_v_mag;

    //Radius
    int m_radius;
    
    //Identification
    unsigned int m_id;
    bool m_colliding;
public:
    //SFML
    sf::Color m_color;
    sf::CircleShape m_shape;
    sf::RenderWindow *m_window;

    Particle(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f acc, int radius, unsigned int id, float v_mag, sf::RenderWindow *window)
    :m_pos(pos.x, pos.y), m_vel(vel.x, vel.y), m_acc(acc.x, acc.y)
    {
       m_radius = radius;
       m_id     = id;
       m_window = window;
       m_v_mag  = v_mag;
    }
   
public: 
    void updateData(struct p_data_t& p_data);
    void drawBoundingBox();
    void draw(bool DRAW_OUTLINE, int PARTICLE_COUNT);

};

#endif