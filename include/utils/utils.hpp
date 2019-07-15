#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>

//Print Macros
#define LOG(label, value) std::cout << label << value << std::endl;
#define PRINT(X) std::cout << X << std::endl;

///////////////////////////////////
// LEGACY SF VECTOR HELPER FUNCS //
///////////////////////////////////

//Returns the square of the distance between two points
inline float dist2f(sf::Vector2f& a, sf::Vector2f& b)
{
	return ((b.x - a.x) * (b.x - a.x)) + ((b.y - a.y) * (b.y - a.y));
}

//In place multiplication of a vector by a constant
inline sf::Vector2f mult2f(sf::Vector2f& a, float C)
{
	a.x *= C;
	a.y *= C;

	return a;
}

// Multiplies a vector by a constant but returns a copy without modifying the original
inline sf::Vector2f mult2f_cpy(sf::Vector2f a, float C)
{
	return sf::Vector2f(a.x * C, a.y *C);
}

inline float mag2f(sf::Vector2f& a)
{
	return sqrt(a.x*a.x + a.y*a.y);
}

inline float dot2f(sf::Vector2f&a, sf::Vector2f&b)
{
	return ((a.x * b.x) + (a.y * b.y));
}

//////////////////////
// FUNCTIONS IN USE //
//////////////////////

inline int random(int a, int b)
{
	return rand() % (b - a) + a;
}

inline float frandom(float a, float b)
{
	return a + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(b-a)));
}
//Concatenates two integers
unsigned long int_concat(unsigned long a, unsigned long b);


// Converts a string to an integer in which the integer is each of the strings char character's true integer value concatenated one after another
// This is meant to be used like a hash function (except of course in this case, no hashing is done, and collisions are not possible)
unsigned long stringtocharval(const char *string);


// Linearly Maps a given value within a given range to a new value within a new range */
double l_map(double x, double input_start, double input_end, double output_start, double output_end);

// hue: 0-360°; sat: 0.f-1.f; val: 0.f-1.f
sf::Color hsv(int hue, float sat, float val);

char* load_file(char const* path);
#endif