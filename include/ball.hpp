#ifndef BALL_H
#define BALL_H

#include "basic.hpp"
#include "utils.hpp"

class Ball
{
public:
	//Kinematic Data
	sf::Vector2f m_pos; //Position
	sf::Vector2f m_vel; //Velocity
	sf::Vector2f m_acc; //Acceleration
	sf::Vector2f m_p;   //Momentum

	//Physical Constants for Hertzian Contact
	float v_p; //Poisson's Ratio (Ratio of transverse to axial strain)
	float E;
	//Physical Data
	float m_mass;
	float m_radius;
	
	//Identification
	unsigned int id;
	bool colliding;
	

	//SFML Data
	sf::Color m_color;
	sf::Font font;
	sf::Text text;
	float render_radius;
private:	
	sf::RenderWindow *m_window;
	sf::CircleShape m_shape;
	

public:
	//Constructor
	Ball(sf::Vector2f pos, sf::Vector2f vel, float radius, float mass, sf::RenderWindow *window)
		:m_pos(pos.x, pos.y), m_vel(vel.x, vel.y), m_acc(0.0f,0.0f), m_mass(mass), m_color(sf::Color::Blue)
	{
		v_p = 0.4999;
		E = 15;
		
		m_radius = radius;
		//m_radius = render_radius * 0.0001;
		m_shape.setRadius(m_radius);
		m_shape.setPointCount(100);
		m_shape.setOrigin(m_radius,m_radius);

		m_window = window;

		m_p = m_vel;
		mult2f(m_p, mass);

	    // if (!font.loadFromFile("../assets/font.ttc"))
	    // {
	    //     LOG("[ERROR]: Font Not Found")
	    // }
	    // text.setFont(font);
	    // text.setFillColor(sf::Color::White);
	    // text.setCharacterSize(100);

	}

	//Ball Physics Calculations
	void applyForce(sf::Vector2f force, double time_delta);
	void update(double time_delta);

	//Rendering
	void draw();





};


#endif