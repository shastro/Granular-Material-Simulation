#ifndef UTILS_H
#define UTILS_H

#include "basic.hpp"

#define LOG(x) std::cout << x << std::endl;

//Returns the square of the distance between two points
inline float dist2f(sf::Vector2f& a, sf::Vector2f& b)
{
	return ((b.x - a.x) * (b.x - a.x)) + ((b.y - a.y) * (b.y - a.y));
}

inline sf::Vector2f mult2f(sf::Vector2f& a, float C)
{
	a.x *= C;
	a.y *= C;

	return a;
}

inline float mag2f(sf::Vector2f& a)
{
	return sqrt(a.x*a.x + a.y*a.y);
}

inline float dot2f(sf::Vector2f&a, sf::Vector2f&b)
{
	return ((a.x * b.x) + (a.y * b.y));
}

inline int random(int a, int b)
{
	return rand() % (b - a) + a;
}

inline float frandom(float a, float b)
{
	return a + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(b-a)));
}

// Linearly Maps a given value within a given range to a new value within a new range */
double l_map(double x, double input_start, double input_end, double output_start, double output_end);
// hue: 0-360°; sat: 0.f-1.f; val: 0.f-1.f
sf::Color hsv(int hue, float sat, float val);
#endif