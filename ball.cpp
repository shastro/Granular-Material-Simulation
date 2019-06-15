#include "ball.hpp"


/////////////
// PHYSICS //
/////////////


void Ball::applyForce(sf::Vector2f force)
{
	m_acc = m_acc + mult2f(force, 1 / m_mass);

}

//Updates position and velocities of objects, performs no or very little physics calculation, is only responsible for translating acceleration to position
void Ball::update()
{
	m_acc = m_acc + sf::Vector2f(0.0, 0.025); //Gravity
	m_vel = m_vel + m_acc;
	m_pos = m_pos + m_vel;
	m_acc = sf::Vector2f(0, 0);

	if(mag2f(m_vel) < 0.01){
		mult2f(m_vel, 0);
	}


	// if (Ball::is_Ball_Collide(other)) {

	// 	// sf::Vector2f norm = m_pos - other.m_pos; 
	// 	// // Calculate displacement required
	// 	// float fOverlap = 0.5f * (mag2f(norm) - m_radius - other.m_radius);

	// 	// // Displace Current Ball away from collision
	// 	// // ball.px -= fOverlap * (ball.px - target.px) / fDistance;
	// 	// // ball.py -= fOverlap * (ball.py - target.py) / fDistance;

	// 	// m_pos = m_pos - mult2f(norm, fOverlap/mag2f(norm));
	// 	// // Displace Target Ball away from collision
	// 	// // target.px += fOverlap * (ball.px - target.px) / fDistance;
	// 	// // target.py += fOverlap * (ball.py - target.py) / fDistance;

	// 	// other.m_pos = other.m_pos + mult2f(norm, fOverlap/mag2f(norm));


	// 	sf::Vector2f force = m_pos - other.m_pos;
	// 	force = mult2f(force, mag2f(force));
	// 	applyForce(mult2f(force, 100/ (float) dist2f(m_pos, other.m_pos)));

	// }


	float c_e = 0.8; //Coefficient of Elasticity
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
	m_vel = mult2f(m_vel, 0.9999);

}

//Spring Force, sums of momentum divided by radius squared

///////////////
// RENDERING //
///////////////


void Ball::draw() {
	sf::CircleShape center_disp;

	if(colliding){
		m_color = sf::Color::Red;
	}else{
		double hue_val = l_map((double)mag2f(m_vel), 0.0, 5, 235, 130);
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