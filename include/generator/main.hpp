#ifndef MAIN_H
#define MAIN_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "rapidjson.h"
#include "document.h"
#include "filewritestream.h"
#include "writer.h"
#include "prettywriter.h"

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
/*
Holds basic window information for particle placement initialization
*/
struct window_t{

	int width;
	int height;
};
#endif