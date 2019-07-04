#include "ball.hpp"


/////////////
// PHYSICS //
/////////////


void Ball::applyForce(sf::Vector2f force, double time_delta)
{
	
	m_acc = m_acc + mult2f(force, 1 / m_mass);

}

//Updates position and velocities of objects, performs no or very little physics calculation, is only responsible for translating acceleration to position
void Ball::update(double time_delta, rj::Value *cur_particle)
{

	applyForce(sf::Vector2f(0.0, 2000), time_delta);

	sf::Vector2f m_acc_cpy = m_acc;
	sf::Vector2f m_vel_cpy = m_vel;

	m_vel = m_vel + mult2f_cpy(m_acc, time_delta);
	m_pos = m_pos + mult2f_cpy(m_vel, time_delta);
	
	
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

	// Data Writing //
	rj::Value particle_data(rj::kObjectType);

	// Position //
		rj::Value p_position(rj::kObjectType);
		rj::Value p_position_x;
		rj::Value p_position_y;

		p_position_x.SetFloat(m_pos.x);
		p_position_y.SetFloat(m_pos.y);

		p_position.AddMember("x", p_position_x, datadoc->GetAllocator());
		p_position.AddMember("y", p_position_y, datadoc->GetAllocator());

		particle_data.AddMember("position", p_position, datadoc->GetAllocator());

	// Velocity //
		rj::Value p_velocity(rj::kObjectType);
		rj::Value p_velocity_x;
		rj::Value p_velocity_y;

		p_velocity_x.SetFloat(m_vel.x);
		p_velocity_y.SetFloat(m_vel.y);

		p_velocity.AddMember("x", p_velocity_x, datadoc->GetAllocator());
		p_velocity.AddMember("y", p_velocity_y, datadoc->GetAllocator());

		particle_data.AddMember("velocity", p_velocity, datadoc->GetAllocator());

	// Acceleration //
		rj::Value p_acceleration(rj::kObjectType);
		rj::Value p_acceleration_x;
		rj::Value p_acceleration_y;

		p_acceleration_x.SetFloat(m_acc.x);
		p_acceleration_y.SetFloat(m_acc.y);

		p_acceleration.AddMember("x", p_acceleration_x, datadoc->GetAllocator());
		p_acceleration.AddMember("y", p_acceleration_y, datadoc->GetAllocator());

		particle_data.AddMember("acceleration", p_acceleration, datadoc->GetAllocator());

	// Radius //

		rj::Value radius;
		radius.SetInt(m_radius);
		particle_data.AddMember("radius", radius, datadoc->GetAllocator());

	// Velocity Magnitude //	

		rj::Value vel_mag;
		vel_mag.SetFloat(mag2f(m_vel));
		particle_data.AddMember("velocity_magnitude", vel_mag, datadoc->GetAllocator());

	// Add all Particle data to current particle
	cur_particle->AddMember("particle_data", particle_data, datadoc->GetAllocator());
	
	//Reset Acceleration to zero after recording
	m_acc = sf::Vector2f(0, 0);

}

//Spring Force, sums of momentum divided by radii sum squared

//////////////////
// DATA WRITING //
//////////////////

void Ball::attachDocument(rj::Document *datadoc)
{
	this->datadoc = datadoc;
}