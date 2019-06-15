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
	applyForce(sf::Vector2f(0.0, 300), time_delta);

	sf::Vector2f m_acc_cpy = m_acc;
	sf::Vector2f m_vel_cpy = m_vel;

	m_vel = m_vel + mult2f_cpy(m_acc, time_delta);
	m_pos = m_pos + mult2f_cpy(m_vel, time_delta);
	m_acc = sf::Vector2f(0, 0);
	
	mult2f(m_p, m_mass); //Momenta

	//Speed Clamping at Rest
	if(mag2f(m_vel) < 0.00005){
		mult2f(m_vel, 0);
	}

	float c_e = 0.5; //Coefficient of Elasticity (roughly speaking) this only applies to wall collision 

	//Edge Detection
	if (m_pos.x + m_radius > (*m_window).getSize().x) {
		m_pos.x = (*m_window).getSize().x - m_radius;
		m_vel.x *= -c_e;
	}
	if (m_pos.x - m_radius < 0) {
		m_pos.x = m_radius;
		m_vel.x *= -c_e;
	}

	if (m_pos.y +  m_radius > (*m_window).getSize().y) {
		m_pos.y = (*m_window).getSize().y - m_radius;
		m_vel.y *= -c_e;
	}

	if (m_pos.y - m_radius < 0) {
		m_pos.y = m_radius;
		m_vel.y *= -c_e;
	}

	//Air Drag
	//mult2f(m_vel, 0.975);
	applyForce(mult2f_cpy(m_vel, -10), time_delta);

}

//Spring Force, sums of momentum divided by radii sum squared

///////////////
// RENDERING //
///////////////


void Ball::draw() {
	sf::CircleShape center_disp;

	if(colliding){
		m_color = sf::Color::Red;
	}else{
		double hue_val = l_map((double)mag2f(m_vel), 0.0, 10, 235, 130);
		m_color = hsv((int)hue_val, 1.0f, 1.0f);
	}

	//Particle
	m_shape.setFillColor(m_color);
	m_shape.setPosition(m_pos);
	m_window->draw(m_shape);
	colliding = false;

	//Center Display
	center_disp.setRadius(5);
	center_disp.setOrigin(5, 5);
	center_disp.setPosition(m_pos);
	center_disp.setFillColor(sf::Color::Yellow);
	m_window->draw(center_disp);


	//Text
	// text.setPosition(m_pos);
	// m_window->draw(text);
}