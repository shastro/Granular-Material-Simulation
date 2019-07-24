#ifndef BALL_H
#define BALL_H

#include "engine.hpp"
#include "utils.hpp"

class Bucket;

class Ball
{
public:
	//Kinematic Data
	Eigen::Vector2f m_pos; //Position
	Eigen::Vector2f m_vel; //Velocity
	Eigen::Vector2f m_acc; //Acceleration
	Eigen::Vector2f m_p;   //Momentum

	//Physical Constants for Hertzian Contact
	double v_p; //Poisson's Ratio (Ratio of transverse to axial strain)
	double E;   // Young's Modulus

	//Physical Data
	float m_mass;
	float m_radius;
	
	//Identification
	unsigned int id;
	bool colliding;

	std::vector<int> bucketids;

private:
	bool debug;
	struct window_t *m_window;	

	rj::Writer<rj::StringBuffer> *dw;	

public:
	//Constructor
	Ball(Eigen::Vector2f pos, Eigen::Vector2f vel, float radius, float mass, struct window_t *window, unsigned int id_in, double P_RATIO, double YOUNGS_MODULUS)
		:m_pos(pos[0], pos[1]), m_vel(vel[0], vel[1]), m_acc(0.0f,0.0f), m_mass(mass)
	{
		this->id = id_in;
		
		//Constant Initialization
		v_p = P_RATIO;
		E = YOUNGS_MODULUS;
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
	void update(double time_delta, int b_zone);
	void attachWriter(rj::Writer<rj::StringBuffer> *dw);
	void writeData();
	void addBucket(int bucketid);
	void clearBuckets();





};


#endif