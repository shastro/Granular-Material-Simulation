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
	double timestep;
	int   steps;
	double dt;

//Simulation Data
	std::vector<Ball> Not_Collided;
	std::vector<Ball> Collided;
	int n;

public:
	Simulation_Engine(int steps, int n, sf::RenderWindow *window) {
		//Time and Random number initialization
		srand(time(NULL));

		this->n = n;
		this->m_window = window;
		this->steps = steps;

		//Create Balls with random initial data.
		for (int i = 0; i < n; i++) {
		
			int radius = random(20, 55); //Random between 50 and 150;
			int pos_x  = random(radius + 2, (*m_window).getSize().x - radius - 2); //Places objects randomely with small buffer to prevent wall intersections on creation
			int pos_y  = random(radius + 2, (*m_window).getSize().y - radius - 2);
		
			float vel_x = frandom(-1.3, 1.3);
			float vel_y = frandom(-1.3, 1.3);

			float mass = frandom(500, 1500);
			Ball *ball = new Ball(sf::Vector2f((float)pos_x, (float)pos_y), sf::Vector2f(vel_x, vel_y), radius, mass, m_window);
			ball->id = i;
			auto s = std::to_string(ball->id);
			ball->text.setString(s.c_str());
			Not_Collided.emplace_back(*ball);
		
		}
	}

	void detectCollisions();
	void calcSteps();
	void drawElements();

private:
	void applyBallResponse(Ball& ball, Ball& ball2);
	bool checkBallIntersect(Ball& ball1, Ball& ball2);












};



#endif