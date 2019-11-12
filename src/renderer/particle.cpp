#include "particle.hpp"

void Particle::drawBoundingBox()
{
    sf::RectangleShape bounding_box;

    bounding_box.setPosition(m_pos.x - m_radius, m_pos.y - m_radius);
    bounding_box.setSize(sf::Vector2f(2 * m_radius, 2 * m_radius));
    bounding_box.setOutlineColor(sf::Color::Black);
    bounding_box.setFillColor(sf::Color(255,255,255,0));
    bounding_box.setOutlineThickness(2);


    int point_radius = 5;

    sf::CircleShape ul;
    sf::CircleShape bl;
    sf::CircleShape ur;
    sf::CircleShape br;

    ul.setRadius(point_radius);
    bl.setRadius(point_radius);
    ur.setRadius(point_radius);
    br.setRadius(point_radius);

    ul.setOrigin(point_radius, point_radius);
    bl.setOrigin(point_radius, point_radius);
    ur.setOrigin(point_radius, point_radius);
    br.setOrigin(point_radius, point_radius);

    ul.setPosition(m_pos.x - m_radius, m_pos.y - m_radius);
    bl.setPosition(m_pos.x - m_radius, m_pos.y + m_radius);
    ur.setPosition(m_pos.x + m_radius, m_pos.y - m_radius);
    br.setPosition(m_pos.x + m_radius, m_pos.y + m_radius);

    ur.setFillColor(sf::Color::Red);
    bl.setFillColor(sf::Color::Red);
    ul.setFillColor(sf::Color::Green);
    br.setFillColor(sf::Color::Green);

    m_window->draw(bounding_box);
    m_window->draw(ul);
    m_window->draw(bl);
    m_window->draw(ur);
    m_window->draw(br);
}

void Particle::draw(bool DRAW_OUTLINE, int PARTICLE_COUNT)
{

    sf::CircleShape center_disp;


    // if(colliding){
    //     m_color = sf::Color::Red;
    // }else{
    double hue_val;
    int min = 0;
    int max = 500000;
    if (m_v_mag < max) {
        hue_val = l_map(m_v_mag, min, max, 235, 0);

    } else {
        hue_val = 0;
    }
    //hue_val = l_map(m_id, 0, PARTICLE_COUNT, 235, 0);

    m_color = hsv((int)hue_val, 1.0f, 1.0f);
    //}

    // PRINT("DRAWCALL PARTICLE")
    //Particle
    m_shape.setOrigin(m_radius, m_radius);
    m_shape.setRadius(m_radius);
    m_shape.setFillColor(m_color);
    m_shape.setPosition(m_pos);


 
    //bounding_box.setFillColor(sf::Color::White);

    if (m_radius < 10) {
        m_shape.setPointCount(10);
    }

    if (DRAW_OUTLINE) {
        m_shape.setOutlineColor(sf::Color::Black);
        m_shape.setOutlineThickness(2);
    }
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

