#include "ball.hpp"


/////////////
// PHYSICS //
/////////////


void Ball::applyForce(Eigen::Vector2f force, double time_delta)
{
	
	m_acc = m_acc + (force * (1 / m_mass));

}

//Updates position and velocities of objects, performs no or very little physics calculation, is only responsible for translating acceleration to position
void Ball::update(double time_delta, int b_zone)
{

	
	//applyForce(Eigen::Vector2f(0.0, 30000000), time_delta); //Gravity 
	//m_acc = m_acc + Eigen::Vector2f(0.0, 800000000);

	Eigen::Vector2f m_acc_cpy = m_acc;
	Eigen::Vector2f m_vel_cpy = m_vel;

	//Integration of Newton's Laws

	m_vel = m_vel + m_acc * time_delta;
	m_vel[1] = m_vel[1] + 100;
	m_pos = m_pos + m_vel * time_delta;
	
	
	m_p = m_vel * m_mass; //Momenta

	//Speed Clamping at Rest
	if(m_vel.squaredNorm() < 0.00005){
		m_vel = m_vel * 0;
	}

	float c_e = 0.5; //Coefficient of Elasticity (roughly speaking) this only applies to wall collision 


	//Edge Detection
	if (m_pos[0] + m_radius > m_window->width - b_zone) {
		m_pos[0] = m_window->width - b_zone - m_radius;
		m_vel[0] *= -c_e;
	}
	if (m_pos[0] - m_radius < b_zone) {
		m_pos[0] = m_radius + b_zone;
		m_vel[0] *= -c_e;
	}

	if (m_pos[1] +  m_radius > m_window->height - b_zone) {
		m_pos[1] = m_window->height - b_zone - m_radius;
		m_vel[1] *= -c_e;
	}

	if (m_pos[1] - m_radius < b_zone) {
		m_pos[1] = m_radius + b_zone;
		m_vel[1] *= -c_e;
	}

	//Air Drag
	//applyForce(mult2f_cpy(m_vel, -10), time_delta);
	
	//Reset Acceleration to zero
	m_acc = Eigen::Vector2f(0, 0);

}

//Spring Force, sums of momentum divided by radii sum squared

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

		double vel_mag = (double)m_vel.norm();
		if(std::isnan(vel_mag)){
			dw->Null();
		}else{
			dw->Double(vel_mag);
		}
	
	dw->EndObject();
}

void Ball::addBucket(int bucketid)
{
	bucketids.emplace_back(bucketid);
	//PRINT(bucketids.size())
}

void Ball::clearBuckets()
{
	bucketids.clear();
	bucketids.shrink_to_fit();
	std::vector<int>().swap(bucketids);
}


Ball::~Ball()
{
	//printf("Ball %d Deleted\n", id);
}

