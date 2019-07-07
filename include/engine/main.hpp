#ifndef MAIN_H
#define MAIN_H


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

#define PRINT(X) std::cout << X << std::endl;

enum COLLISION_MODE{HERTZ, HERTZ_DAMP};

/* Holds basic window information for particle placement initialization
*/
struct window_t{

	int width;
	int height;
};

/* Holds pertinant simulation config data that the Simulation_Engine Class Needs
*/

struct config_data_t{

	bool MINIMIZE_DATA;

};
#endif