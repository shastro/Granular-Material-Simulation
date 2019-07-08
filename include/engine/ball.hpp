#ifndef BALL_H
#define BALL_H

#include "main.hpp"
#include "utils.hpp"

class Ball
{
public:
	//Kinematic Data
	Eigen::Vector2f m_pos; //Position
	Eigen::Vector2f m_vel; //Velocity
	Eigen::Vector2f m_acc; //Acceleration
	Eigen::Vector2f m_p;   //Momentum

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

	rj::Writer<rj::StringBuffer> *dw;	

public:
	//Constructor
	Ball(Eigen::Vector2f pos, Eigen::Vector2f vel, float radius, float mass, struct window_t *window, unsigned int id_in)
		:m_pos(pos[0], pos[1]), m_vel(vel[0], vel[1]), m_acc(0.0f,0.0f), m_mass(mass)
	{
		this->id = id_in;
		
		//Constant Initialization
		v_p = 0.5;
		E = 30;
		debug = false;
		
		//Member Assignment
		m_radius = radius;
		m_window = window;
		
		//Momentum
		m_p = m_vel;
		m_p = m_p * mass;


	}
	//Destructor
	~Ball();


	//Ball Physics Calculations
	void applyForce(Eigen::Vector2f force, double time_delta);
	void update(double time_delta);
	void attachWriter(rj::Writer<rj::StringBuffer> *dw);
	void writeData();






};


#endif