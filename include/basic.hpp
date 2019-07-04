#ifndef BASIC_H
#define BASIC_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "rapidjson/document.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/ostreamwrapper.h"
namespace rj = rapidjson;

#include <iostream>
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