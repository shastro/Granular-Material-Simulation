#ifndef DRAW_H
#define DRAW_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>

namespace rj = rapidjson;

#include "utils.hpp"
#include "particle.hpp"
#include <vector>

struct p_data_t {

    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::Vector2f acc;
    float v_mag;

};

#endif