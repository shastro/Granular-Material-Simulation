#include "sim.hpp"


//Checks ball collision between two balls
bool Simulation_Engine::checkBallIntersect(Ball& ball1, Ball& ball2)
{
	if (dist2f(ball1.m_pos, ball2.m_pos) < ((ball1.m_radius + ball2.m_radius) * (ball1.m_radius + ball2.m_radius))) {

		//std::cout << "Ballid: " << ball1.id << " " << "Targid: " << ball2.id << std::endl;
		return true;

	} else {
		return false;
	}
}
void Simulation_Engine::detectCollisions()
{
	for (auto & ball : Not_Collided) {
		for (auto & other : Not_Collided) {
			if (ball.id != other.id) {
				if (checkBallIntersect(ball, other)) {
					ball.colliding = true;
					other.colliding = true;

					applyBallResponse(ball, other);
				}
			}

		}
	}
}
void Simulation_Engine::applyBallResponse(Ball& ball1, Ball& ball2)
{
	sf::Vector2f normal = ball1.m_pos - ball2.m_pos; //Vector normal to point of contact
	float dist = mag2f(normal); //Capture the distance
	mult2f(normal, 1.0f / mag2f(normal)); //Normalize the normal vector
	float overlap = dist - (ball1.m_radius - ball2.m_radius);
	LOG(overlap)
	//Calculate Effective Modulus of Elasticity
	float E_eff = 1.0f / (((1 - ball1.v_p * ball1.v_p) / ball1.E) + ((1 - ball2.v_p * ball2.v_p) / ball1.E)); 
	float r_eff = 1.0f / ((1/ball1.m_radius) + (1/ball2.m_radius));

	//Hertzian Stiffness
	float k_hz  = (1.33333333) * sqrt(r_eff) * E_eff;
	float f_mag = k_hz * pow(overlap, 1.5);
	//std::cout << f_mag << std::endl;
	sf::Vector2f force = mult2f_cpy(normal, f_mag);

	//std::cout << mag2f(force) << std::endl;
	ball1.applyForce(force, fSimElapsedTime);	// 	sf::Vector2f force = m_pos - other.m_pos;
	ball2.applyForce(mult2f(force, -1), fSimElapsedTime);


}


//Handles Updating Object postions, velocities, momenta
// IE collision response at a macro level
void Simulation_Engine::calcSteps()
{
	for (int i = 0; i < n; i++) {
		Not_Collided.at(i).update(fSimElapsedTime);
	}

}

//Handles Drawing
void Simulation_Engine::drawElements()
{
	for (int i = 0; i < n; i++) {
		Not_Collided.at(i).draw();
	}
}

void Simulation_Engine::updateTimeData()
{
	fSimElapsedTime = dt / (double) nSimulationSubSteps;
}

void Simulation_Engine::simLoop()
{
	clock_t start = clock();
	//MAIN LOGIC//
	for (int i = 0; i < nSimulationSubSteps; i++) {
		detectCollisions();
		calcSteps();
	}
	drawElements();


	clock_t end = clock();
	dt = (double) (end - start) / (CLOCKS_PER_SEC * 0.06);
	//LOG(dt)
	updateTimeData();

}