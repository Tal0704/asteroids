#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>

#define PI 3.14159265

float angleFromVect(const sf::Vector2f& v);

float distance(const sf::Vector2f& left, const sf::Vector2f& right);

sf::Vector2f velocityFromSpeed(float speed, float angle);
