// #include "sim.hpp"

// Simulation_Engine::Simulation_Engine(struct window_t *window, rj::Writer<rj::StringBuffer> *dw, struct config_data_t *config)
// {
// 	//Time and Random number initialization
// 	srand(time(NULL));

// 	this->window = window;
// 	this->conf = config;
// 	this->dw = dw;

// 	nParticles = conf->PARTICLE_COUNT;
// 	this->nSimulationSubSteps = conf->SUB_FRAME_COUNT;
// 	m_COLLISION_MODE = conf->COLLISION_MODE;

// 	//////////////////
// 	// Spatial Hash //
// 	//////////////////
// 	int cellsize = 4 * conf->MAX_RADIUS;
// 	shash = new SpatialHash<Ball>(window->width, window->height, cellsize);
// 	shash->attach_DetectCollision(checkBallIntersect);
// 	shash->attach_ApplyCollision(applyBallResponse);

// 	//Writing CellSize to Data File
// 	dw->Key("CELLSIZE");
// 	dw->Uint(cellsize);

// 	//Create Balls with random initial data.
// 	for (int i = 0; i < nParticles; i++) {

// 		int radius;
// 		if (conf->MIN_RADIUS != conf->MAX_RADIUS) {
// 			radius = random(conf->MIN_RADIUS, conf->MAX_RADIUS);
// 		} else {
// 			radius = conf->MIN_RADIUS;
// 		}

// 		int pos_x  = random(radius + 2, window->width  - window->spawnbuffer - radius - 2); //Places objects randomely with small buffer to prevent wall intersections on creation
// 		int pos_y  = random(radius + 2, window->height - window->spawnbuffer - radius  - 2);

// 		float s_vel = (float)conf->SPAWN_VEL;
// 		float vel_x = frandom(-1.0 * s_vel, s_vel);
// 		float vel_y = frandom(-1.0 * s_vel, s_vel);

// 		float mass = radius * radius * 3.14159 * 0.25;

// 		Ball *ball = new Ball(Eigen::Vector2f((float)pos_x, (float)pos_y), Eigen::Vector2f(vel_x, vel_y), radius, mass, window, i, conf->P_RATIO, conf->YOUNGS_MODULUS);
// 		ball->attachWriter(dw);

// 		vecBalls.push_back(ball);

// 	}
// 	PRINT("ENGINE CREATED")
// }

// //Destructor
// Simulation_Engine::~Simulation_Engine()
// {
// 	PRINT("ENGINE DESTROYED")
// 	// for(auto &ball : vecBalls){
// 	// 	delete &ball;
// 	// }
// 	std::vector<Ball*>().swap(vecBalls);
// }

// //Checks ball collision between two balls
// bool Simulation_Engine::checkBallIntersect(Ball  *a, Ball *b)
// {
// 	if ((a->m_pos - b->m_pos).squaredNorm() < ((a->m_radius + b->m_radius) * (a->m_radius + b->m_radius))) {
// 		return true;

// 	} else {
// 		return false;
// 	}
// }
// void Simulation_Engine::detectCollisions()
// {

// 	if (conf->OPTIMIZE) {
		
// 		shash->build(vecBalls);
// 		shash->collidePairs();

// 	} else {
// 		//brute force
// 		for (auto ball : vecBalls) {
// 			for (auto other : vecBalls) {
// 				if (ball->m_Id != other->m_Id) {
// 					if (checkBallIntersect(ball, other)) {
// 						ball->colliding = true;
// 						other->colliding = true;

// 						applyBallResponse(ball, other);
// 					}
// 				}
// 			}
// 		}
// 	}


// }
// void Simulation_Engine::applyBallResponse(Ball *a, Ball *b)
// {
// 	//Dereferencing
// 	Ball ball1 = *a;
// 	Ball ball2 = *b;
// 	//Support for multiple different types of collision response
// 	switch (m_COLLISION_MODE) {
// 	case (HERTZ):

// 	{	//Scope Wrapping

// 		////////////////////

// 		// Normal Vector //

// 		Eigen::Vector2f normal = ball1.m_pos - ball2.m_pos; //Vector normal to point of contact
// 		float dist = normal.norm(); //Capture the distance
// 		normal.normalize(); //Normalize the normal vector

// 		////////////////////

// 		// Overlap //

// 		float overlap = (ball1.m_radius + ball2.m_radius) - dist;
// 		//overlap = overlap * overlap * overlap;

// 		///////////////////

// 		// Calculate Effective Modulus of Elasticity //

// 		float E_eff = 1.0f / (((1 - ball1.v_p * ball1.v_p) / ball1.E) + ((1 - ball2.v_p * ball2.v_p) / ball1.E));
// 		float r_eff = 1.0f / ((1 / ball1.m_radius) + (1 / ball2.m_radius));

// 		//////////////////

// 		// Hertzian Stiffness //

// 		float k_hz  = (1.33333333) * sqrt(r_eff) * E_eff;
// 		float f_mag = k_hz * pow(overlap, 1.5);
// 		Eigen::Vector2f force = normal * f_mag;

// 		force = force;
// 		//////////////////

// 		// ApplyForce //

// 		ball1.applyForce(force, fSimElapsedTime);
// 		//ball2.applyForce((force * -1), fSimElapsedTime);


// 	}//Scope Wrapping

// 	break;
// 	case (HERTZ_DAMP):

// 	{	//Scope Wrapping

// 		// Normal Vector //

// 		Eigen::Vector2f normal = ball1.m_pos - ball2.m_pos; //Vector normal to point of contact
// 		float dist = normal.norm(); //Capture the distance
// 		normal.normalize(); //Normalize the normal vector

// 		/////////////////////////

// 		// Overlap //
// 		float overlap = (ball1.m_radius + ball2.m_radius) - dist;
// 		//overlap = overlap * overlap * overlap;

// 		/////////////////////////

// 		// Calculate Effective Modulus of Elasticity //

// 		float E_eff = 1.0f / (((1 - ball1.v_p * ball1.v_p) / ball1.E) + ((1 - ball2.v_p * ball2.v_p) / ball1.E));
// 		float r_eff = 1.0f / ((1 / ball1.m_radius) + (1 / ball2.m_radius));

// 		/////////////////////////

// 		// Damping Calculations //

// 		float dmp = 0.9999; //Damping Coeff
// 		float v_rel = ball1.m_vel.dot(normal) + ball2.m_vel.dot(normal);
// 		Eigen::Vector2f damp_force = normal * (v_rel * dmp);
// 		ball1.m_vel = ball1.m_vel * dmp;
// 		ball2.m_vel = ball2.m_vel * dmp;

// 		/////////////////////////

// 		// Hertzian Stiffness //

// 		float k_hz  = (1.33333333) * sqrt(r_eff) * E_eff;
// 		float f_mag = k_hz * pow(overlap, 1.5);
// 		Eigen::Vector2f force = normal * f_mag;

// 		////////////////////////


// 		// Apply forces //
// 		//if(ball1.force_applied_count < 1){
// 		ball1.applyForce(force, fSimElapsedTime);
// 		//}
// 		ball1.force_applied_count++;
// 		//ball2.applyForce((force * -1), fSimElapsedTime);


// 		//////////////////////

// 		// ball1.applyForce(damp_force, fSimElapsedTime);
// 		// ball2.applyForce(mult2f(damp_force, -1), fSimElapsedTime);

// 	}//Scope

// 	break;
// 		// default:
// 		// 	LOG("[ERROR] ", "NO COLLISION MODE SELECTED");
// 		// 	exit(1);
// 		// break;
// 	}

// }


// //Handles Updating Object postions, velocities, momenta
// // IE collision response at a macro level
// void Simulation_Engine::calcSteps(int sub_frame)
// {

// 	if (sub_frame == nSimulationSubSteps - 1) {
// 		dw->Key("particles");
// 		dw->StartArray();
// 	}

// 	for (int i = 0; i < vecBalls.size(); i++) {
// 		if (sub_frame == nSimulationSubSteps - 1) {
// 			dw->StartObject();
// 			dw->Key("id");
// 			dw->Uint(vecBalls[i]->m_Id);

// 			// PHYSICS //
// 			vecBalls[i]->update(fSimElapsedTime);
// 			vecBalls[i]->writeData();
// 			////////////
// 			dw->EndObject();
// 	 	}else if (sub_frame != nSimulationSubSteps - 1) {
// 			///////
// 			vecBalls[i]->update(fSimElapsedTime);
// 			///////
// 		} //If MINIMIZE_DATA is true but its not the last sub_frame do not write data

// 		//LOG("PARTICLE: ", vecBalls[i].id)
// 		//PRINT(vecBalls[i].force_appqlied_count);

// 	}

// 	if (sub_frame == nSimulationSubSteps - 1) {
// 		dw->EndArray();

// 	}





// }

// void Simulation_Engine::simLoop()
// {
// 	// float radius = 15;
// 	// float mass = radius * radius * 3.14159 * 0.25;
// 	// Ball *ball = new Ball(Eigen::Vector2f((float)500.0, (float)50.0), Eigen::Vector2f(0.0, 0.0), radius, mass, window, nParticles, conf->P_RATIO, conf->YOUNGS_MODULUS);
// 	// vecBalls.emplace_back(*ball);
// 	// nParticles++;

// 	//MAIN LOGIC//

// 	// SUB FRAME DATA SETUP //
// 	dw->Key("SUBFRAMES");
// 	dw->StartArray();

// 	fSimElapsedTime = (double)conf->TIME_STEP_COEFFICIENT / (double) nSimulationSubSteps;

// 	for (int i = 0; i < nSimulationSubSteps; i++) {

// 		// Build Hash
// 		shash->build(vecBalls);

// 		if ((conf->MINIMIZE_DATA == true) && (i == nSimulationSubSteps - 1)) {
// 			dw->StartObject();

// 			dw->Key("sub_frame");
// 			dw->Uint(0);

// 		} else {
// 			//Do nothing
// 		}
// 		//////////////////////////
// 		// PHYSICS CALCULATIONS //
// 		//                      //
// 		detectCollisions();     //
// 		calcSteps(i);           //
// 		//////////////////////////

// 		if (i == nSimulationSubSteps - 1) {

// 			dw->EndObject();

// 		}

// 		// Clear Hash
// 		shash->clear();
// 		std::cout << '\r' << "Sub-Frame Completion: " << std::setw(8)/* << std::setfill('0') */ << (100 * (float)(i + 1) / (float)nSimulationSubSteps) << "%" << std::flush;

// 	}

// 	dw->EndArray();




// }

// // double Simulation_Engine::fSimElapsedTime;
// // int Simulation_Engine::m_COLLISION_MODE;
