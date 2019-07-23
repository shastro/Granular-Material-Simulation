/** This file holds some general header definitions as well as some declarations useful only to engine.cpp */

#ifndef ENGINE_H
#define ENGINE_H


#include <Eigen/Core>

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>

namespace rj = rapidjson;

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <random>
#include <vector>

#include <math.h>


enum COLLISION_MODE{HERTZ, HERTZ_DAMP};

/* Holds basic window information for particle placement initialization
*/
struct window_t{

	int width;
	int height;
	int spawnbuffer;
};

/* Holds pertinant simulation config data that the Simulation_Engine Class Needs
*/

struct config_data_t{

	int FRAMELIMIT;
	int SUB_FRAME_COUNT;
	int PARTICLE_COUNT;
	int COLLISION_MODE;

	int MEMORY_FRAME_SAVE_THRESHOLD;
	bool MINIMIZE_DATA;

	double TIME_STEP_COEFFICIENT;

	int MIN_RADIUS;
	int MAX_RADIUS;

};
#endif