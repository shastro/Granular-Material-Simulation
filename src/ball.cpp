#include "ball.hpp"


/////////////
// PHYSICS //
/////////////


void Ball::applyForce(sf::Vector2f force, double time_delta)
{
	
	m_acc = m_acc + mult2f(force, 1 / m_mass);

}

//Updates position and velocities of objects, performs no or very little physics calculation, is only responsible for translating acceleration to position
void Ball::update(double time_delta)
{

	applyForce(sf::Vector2f(0.0, 2000), time_delta);

	sf::Vector2f m_acc_cpy = m_acc;
	sf::Vector2f m_vel_cpy = m_vel;

	m_vel = m_vel + mult2f_cpy(m_acc, time_delta);
	m_pos = m_pos + mult2f_cpy(m_vel, time_delta);
	m_acc = sf::Vector2f(0, 0);
	
	mult2f(m_p, m_mass); //Momenta

	//Speed Clamping at Rest
	if(mag2f(m_vel) < 0.0005){
		mult2f(m_vel, 0);
	}

	float c_e = 0.5; //Coefficient of Elasticity (roughly speaking) this only applies to wall collision 

	float b_zone = 100; //Window Edge Buffer
	//Edge Detection
	if (m_pos.x + m_radius > m_window->width - b_zone) {
		m_pos.x = m_window->width - b_zone - m_radius;
		m_vel.x *= -c_e;
	}
	if (m_pos.x - m_radius < b_zone) {
		m_pos.x = m_radius + b_zone;
		m_vel.x *= -c_e;
	}

	if (m_pos.y +  m_radius > m_window->height - b_zone) {
		m_pos.y = m_window->height - b_zone - m_radius;
		m_vel.y *= -c_e;
	}

	if (m_pos.y - m_radius < b_zone) {
		m_pos.y = m_radius + b_zone;
		m_vel.y *= -c_e;
	}

	//Air Drag
	//applyForce(mult2f_cpy(m_vel, -10), time_delta);
	

}

//Spring Force, sums of momentum divided by radii sum squared

