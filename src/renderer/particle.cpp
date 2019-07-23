#include "particle.hpp"


void Particle::draw()
{

    sf::CircleShape center_disp;

    // if(colliding){
    //     m_color = sf::Color::Red;
    // }else{
        double hue_val;
        int min = 0;
        int max = 800000;
        if(m_v_mag < max){
            hue_val = l_map(m_v_mag, min, max, 235, 0);

        }else{
            hue_val = 0;
        }
       
        m_color = hsv((int)hue_val, 1.0f, 1.0f);
    //}

    // PRINT("DRAWCALL PARTICLE")
    //Particle
    m_shape.setOrigin(m_radius,m_radius);
    m_shape.setRadius(m_radius);
    m_shape.setFillColor(m_color);
    m_shape.setPosition(m_pos);
    m_shape.setOutlineColor(sf::Color::Black);
    m_shape.setOutlineThickness(2);
    // LOG("x: ", m_pos.x)
    // LOG("y: ", m_pos.y)
    // LOG("r: ", m_radius)
    m_window->draw(m_shape);
    //colliding = false;

    //Center Display
    // center_disp.setRadius(5);
    // center_disp.setOrigin(5, 5);
    // center_disp.setPosition(m_pos);
    // center_disp.setFillColor(sf::Color::Yellow);
    // m_window->draw(center_disp);


}

void Particle::updateData(struct p_data_t& p_data)
{
    m_pos = p_data.pos;
    m_vel = p_data.vel;
    m_acc = p_data.acc;
    m_v_mag = p_data.v_mag;
}

