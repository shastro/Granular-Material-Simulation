#include "sim.hpp"

Simulation_Engine::Simulation_Engine(int steps, int n, struct window_t *window, int COLLISION_MODE, rj::Writer<rj::StringBuffer> *dw)
 {
	//Time and Random number initialization
	srand(time(NULL));

	this->dw = dw;
	this->n = n;
	this->nSimulationSubSteps = steps;
	m_COLLISION_MODE = COLLISION_MODE;


	//Create Balls with random initial data.
	for (int i = 0; i < n; i++) {
	
		int radius = random(1, 5); //Random between 50 and 150;
		int pos_x  = random(radius + 2, window->width  - 100 - radius - 2); //Places objects randomely with small buffer to prevent wall intersections on creation
		int pos_y  = random(radius + 2, window->height - 100- radius  - 2);
	
		float vel_x = frandom(-1.3, 1.3);
		float vel_y = frandom(-1.3, 1.3);

		float mass = radius * 100;

		Ball *ball = new Ball(sf::Vector2f((float)pos_x, (float)pos_y), sf::Vector2f(vel_x, vel_y), radius, mass, window, i);
		ball->attachWriter(dw);

		vecBalls.emplace_back(*ball);
	
	}
	PRINT("ENGINE CREATED")
}

//Destructor
Simulation_Engine::~Simulation_Engine()
{
	printf("ENGINE DESTROYED\n");
	// for(auto &ball : vecBalls){
	// 	delete &ball;
	// }
	std::vector<Ball>().swap(vecBalls);
}

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
	for (auto & ball : vecBalls) {
		for (auto & other : vecBalls) {
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

	//Support for multiple different types of collision response
	switch(m_COLLISION_MODE){
		case(HERTZ):

			{//Scope Wrapping

			////////////////////

			// Normal Vector //

			sf::Vector2f normal = ball1.m_pos - ball2.m_pos; //Vector normal to point of contact
			float dist = mag2f(normal); //Capture the distance
			mult2f(normal, 1.0f / dist); //Normalize the normal vector

			////////////////////

			// Overlap //

			float overlap = dist - (ball1.m_radius - ball2.m_radius);
			
			///////////////////

			// Calculate Effective Modulus of Elasticity //

			float E_eff = 1.0f / (((1 - ball1.v_p * ball1.v_p) / ball1.E) + ((1 - ball2.v_p * ball2.v_p) / ball1.E)); 
			float r_eff = 1.0f / ((1/ball1.m_radius) + (1/ball2.m_radius));

			//////////////////

			// Hertzian Stiffness //

			float k_hz  = (1.33333333) * sqrt(r_eff) * E_eff;
			float f_mag = k_hz * pow(overlap, 1.5);
			sf::Vector2f force = mult2f_cpy(normal, f_mag);

			//////////////////

			// ApplyForce //

			ball1.applyForce(force, fSimElapsedTime);
			ball2.applyForce(mult2f(force, -1), fSimElapsedTime);


			}//Scope Wrapping

		break;
		case(HERTZ_DAMP):

			{//Scope Wrapping

			// Normal Vector //

			sf::Vector2f normal = ball1.m_pos - ball2.m_pos; //Vector normal to point of contact
			float dist = mag2f(normal); //Capture the distance
			mult2f(normal, 1.0f / dist); //Normalize the normal vector

			/////////////////////////

			// Overlap //
			float overlap = dist - (ball1.m_radius - ball2.m_radius);
			
			/////////////////////////

			// Calculate Effective Modulus of Elasticity //

			float E_eff = 1.0f / (((1 - ball1.v_p * ball1.v_p) / ball1.E) + ((1 - ball2.v_p * ball2.v_p) / ball1.E)); 
			float r_eff = 1.0f / ((1/ball1.m_radius) + (1/ball2.m_radius));

			/////////////////////////

			// Damping Calculations //

			 float dmp = 0.2; //Damping Coeff
			float v_rel = dot2f(ball1.m_vel, normal) + dot2f(ball2.m_vel, normal);
			sf::Vector2f damp_force = mult2f_cpy(normal, v_rel * dmp);
			mult2f(ball1.m_vel,  dmp);
			mult2f(ball2.m_vel,  dmp);

			/////////////////////////

			// Hertzian Stiffness //

			float k_hz  = (1.33333333) * sqrt(r_eff) * E_eff;
			float f_mag = k_hz * pow(overlap, 1.5); 
			sf::Vector2f force = mult2f_cpy(normal, f_mag);

			////////////////////////


			// Apply forces //

			ball1.applyForce(force, fSimElapsedTime);
			ball2.applyForce(mult2f(force, -1), fSimElapsedTime);


			//////////////////////

			// ball1.applyForce(damp_force, fSimElapsedTime);
			// ball2.applyForce(mult2f(damp_force, -1), fSimElapsedTime);

			}//Scope
			
		break;
		// default:
		// 	LOG("[ERROR] ", "NO COLLISION MODE SELECTED");
		// 	exit(1);
		// break;
	}

}


//Handles Updating Object postions, velocities, momenta
// IE collision response at a macro level
void Simulation_Engine::calcSteps()
{
	rj::Value particles(rj::kArrayType);
	dw->Key("particles");
	dw->StartArray();

	for (int i = 0; i < n; i++) {

		dw->StartObject();
		dw->Key("id");
		dw->Uint(vecBalls.at(i).id);

		vecBalls.at(i).update(fSimElapsedTime);

		dw->EndObject();
	}

	dw->EndArray();

}

void Simulation_Engine::updateTimeData()
{
	fSimElapsedTime = dt / (double) nSimulationSubSteps;
}

void Simulation_Engine::simLoop()
{
	clock_t start = clock();
	//MAIN LOGIC//

	// SUB FRAME DATA SETUP //
	dw->Key("SUBFRAMES");
	dw->StartArray();

	for (int i = 0; i < nSimulationSubSteps; i++) {

		dw->StartObject();

        dw->Key("sub_frame");
        dw->Uint(i);

        // PHYSICS CALCULATIONS //
		detectCollisions();
		calcSteps();

		dw->EndObject();

		std::cout << '\r' << "Sub-Frame Completion: " << std::setw(2) << std::setfill('0') << (100 * (float)(i + 1)/(float)nSimulationSubSteps) << "%" << std::flush;

	}
	dw->EndArray();



	clock_t end = clock();
	dt = (double) (end - start) / (CLOCKS_PER_SEC * 0.06); //0.06

	updateTimeData();

}