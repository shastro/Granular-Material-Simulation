#ifndef SIM_H
#define SIM_H

#include <ctime>
#include <cstdlib>

#include "utils.hpp"
#include "ball.hpp"

//Handles all collision checking, evaluation, and calculation of collision response, as well as time step

class Simulation_Engine
{
private:
//Rendering Properties
	sf::RenderWindow *m_window;

//Simulation Properties
	double fSimElapsedTime;
	int   nSimulationSubSteps; //Subframes
	int m_COLLISION_MODE;
public:
	double dt; //Change in time between frames
	bool mouseState; //Mouse state, 0 for released, 1 for clicked

private:
//Simulation Data
	std::vector<Ball> vecBalls;
	std::vector<Ball> Collided;
	int n;

public:
	Simulation_Engine(int steps, int n, sf::RenderWindow *window, int COLLISION_MODE);

	void simLoop();

	void detectCollisions();
	void calcSteps();
	void drawElements();
	void updateTimeData();
	void handleMouseEvent(sf::Vector2f mousePos);

private:
	void applyBallResponse(Ball& ball, Ball& ball2);
	bool checkBallIntersect(Ball& ball1, Ball& ball2);
	Ball findClosestBall(sf::Vector2f mousePos);












};



#endif