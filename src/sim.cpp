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

void Simulation_Engine::applyBallResponse(Ball& ball1, Ball& ball2)
{
	sf::Vector2f force = ball1.m_pos - ball2.m_pos;
	force = mult2f(force, mag2f(force));

	ball1.applyForce(mult2f(force, 25/ (float) dist2f(ball1.m_pos, ball2.m_pos)));	// 	sf::Vector2f force = m_pos - other.m_pos;
	ball2.applyForce(mult2f(force, -25/ (float) dist2f(ball1.m_pos, ball2.m_pos)));
}
void Simulation_Engine::detectCollisions()
{
	for(auto & ball : Not_Collided){
		for(auto & other : Not_Collided){
			if(ball.id != other.id){
				if(checkBallIntersect(ball, other)){
					ball.colliding = true;
					other.colliding = true;

					applyBallResponse(ball, other);
				}
			}
			
		}
	}
}

//Handles Updating Object postions, velocities, momenta
// IE collision response at a macro level
void Simulation_Engine::calcSteps()
{
	for(int i = 0; i < n; i++){
		Not_Collided.at(i).update();
	}

}

//Handles Drawing
void Simulation_Engine::drawElements()
{
	for(int i = 0; i < n; i++){
		Not_Collided.at(i).draw();
	}
}