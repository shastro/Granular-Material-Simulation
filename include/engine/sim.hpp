#ifndef SIM_H
#define SIM_H

#include <ctime>
#include <cstdlib>

#include "engine.hpp"
#include "utils.hpp"
#include "ball.hpp"

//Handles all collision checking, evaluation, and calculation of collision response, as well as time step

class Simulation_Engine
{
private:
//Simulation Properties
	double fSimElapsedTime;
	int   nSimulationSubSteps; //Subframes
	int m_COLLISION_MODE;

	rj::Writer<rj::StringBuffer> *dw;

	struct window_t *window;
	struct config_data_t *conf;
public:
	double dt; //Change in time between frames

private:
//Simulation Data
	std::vector<Ball> vecBalls;
	int nParticles;

public:
	Simulation_Engine(struct window_t *window, rj::Writer<rj::StringBuffer> *dw, struct config_data_t *config);
	~Simulation_Engine();

	
	void simLoop();

	void detectCollisions();
	void calcSteps(int sub_frame);
	void updateTimeData();

private:
	void applyBallResponse(Ball& ball, Ball& ball2);
	bool checkBallIntersect(Ball& ball1, Ball& ball2);












};



#endif