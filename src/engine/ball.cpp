#include "ball.hpp"


/////////////
// PHYSICS //
/////////////

Ball::~Ball()
{
	//printf("Ball %d Deleted\n", id);
}

void Ball::applyForce(Eigen::Vector2f force, double time_delta)
{
	
	m_p = m_p + (force * time_delta);

}

//Updates position and velocities of objects, performs no or very little physics calculation, is only responsible for translating acceleration to position
void Ball::update(double time_delta)
{

	int b_zone = 0;
		
	float gmag = 750 * 5;
	gtheta += 0.0000;
	// gtheta = -3.14159/2;
	applyForce(Eigen::Vector2f(gmag*cos(gtheta + 3.14159/4.0), gmag*sin(gtheta + 3.14159/4.0)), time_delta); //Gravity 

	if((m_p / m_mass).squaredNorm() > 10000){
		m_p.normalize();
		m_p = m_p * 100 * m_mass;
	}

	//Euler Method
	m_vel = m_p / m_mass;
	m_pos = m_pos + m_vel * time_delta;


	//Speed Clamping at Rest
	if(m_vel.squaredNorm() < 0.00005){
		m_vel = m_vel * 0;
	}

	float sigma  = 500; //Scaling factor for forces
	float width  = m_window->width;
	float height = m_window->height;
	// PRINT(m_window->height)
	//Edge Detection
	if (m_pos[0] + m_radius > width) {
		float overlap = (m_pos[0] + m_radius) - width;
		applyForce(Eigen::Vector2f(-sigma*(overlap*overlap), 0), time_delta);
	}
	if (m_pos[0] - m_radius < 0) {
		float overlap = fabs(m_pos[0] - m_radius);
		applyForce(Eigen::Vector2f(sigma*overlap*overlap, 0), time_delta);
	}

	if (m_pos[1] +  m_radius > height) {
		float overlap = m_pos[1] + m_radius - height;
		applyForce(Eigen::Vector2f(0, -sigma*(overlap*overlap)), time_delta);
	}

	if (m_pos[1] - m_radius < 0) {
		float overlap = fabs(m_pos[1] - m_radius);
		applyForce(Eigen::Vector2f(0, sigma*overlap*overlap), time_delta);
	}

	//Air Drag
	//applyForce(mult2f_cpy(m_vel, -10), time_delta);


}


//////////////////
// DATA WRITING //
//////////////////

void Ball::attachWriter(rj::Writer<rj::StringBuffer> *dw)
{
	this->dw = dw;
}

//Writes Particle Data to writer object, should be called after update()
void Ball::writeData()
{

		// Data Writing //
	dw->Key("p_data");
	dw->StartObject();
	// PRINT("YOTE")
	// Position //
		dw->Key("p");
		dw->StartObject();

		dw->Key("x");

		if(std::isnan(m_pos[0])){
			dw->Null();
		}else{
			dw->Double(m_pos[0]);
		}
		dw->Key("y");

		if(std::isnan(m_pos[1])){
			dw->Null();
		}else{
			dw->Double(m_pos[1]);
		}

		dw->EndObject();
	// Velocity //
		dw->Key("v");
		dw->StartObject();

		dw->Key("x");

		if(std::isnan(m_vel[0])){
			dw->Null();
		}else{
			dw->Double(m_vel[0]);
		}
		dw->Key("y");

		if(std::isnan(m_vel[1])){
			dw->Null();
		}else{
			dw->Double(m_vel[1]);
		}

		dw->EndObject();

	// Acceleration //
		dw->Key("a");
		dw->StartObject();

		dw->Key("x");

		if(std::isnan(m_acc[0])){
			dw->Null();
		}else{
			dw->Double(m_acc[0]);
		}
		dw->Key("y");

		if(std::isnan(m_acc[1])){
			dw->Null();
		}else{
			dw->Double(m_acc[1]);
		}

		dw->EndObject();

	// Radius //
		dw->Key("r");
		dw->Uint(m_radius);

	// Velocity Magnitude //	

		dw->Key("v_mag");

		double vel_mag = (double)(m_p/m_mass).norm();
		if(std::isnan(vel_mag)){
			dw->Null();
		}else{
			dw->Double(vel_mag);
		}
	

	dw->EndObject();
}






/////////////
// Getters //
/////////////

float Ball::getRadius() const
{
    return m_radius;
}

float Ball::getMass() const
{
    return m_mass;
}

Eigen::Vector2f &Ball::getPos()
{
    return m_pos;
}

float Ball::getX() const
{
    return m_pos[0];
}

float Ball::getY() const
{
    return m_pos[1];
}