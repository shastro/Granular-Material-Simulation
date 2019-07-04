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

private:
	bool debug;
	struct window_t *m_window;	

	rj::Document *datadoc;	

public:
	//Constructor
	Ball(sf::Vector2f pos, sf::Vector2f vel, float radius, float mass, struct window_t *window)
		:m_pos(pos.x, pos.y), m_vel(vel.x, vel.y), m_acc(0.0f,0.0f), m_mass(mass)
	{
		//Constant Initialization
		v_p = 0.5;
		E = 30;
		debug = false;
		
		//Member Assignment
		m_radius = radius;
		m_window = window;
		
		//Momentum
		m_p = m_vel;
		mult2f(m_p, mass);


	}

	//Ball Physics Calculations
	void applyForce(sf::Vector2f force, double time_delta);
	void update(double time_delta, rj::Value *cur_particle);
	void attachDocument(rj::Document *datadoc);






};


#endif