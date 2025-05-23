#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#define PI 3.14159265

float distance(const sf::Vector2f& left, const sf::Vector2f& right);

sf::Vector2f velocityFromSpeed(float speed, float angle);

#ifndef NDEBUG
#include <iostream>

std::ostream& operator<<(std::ostream& stream, const sf::Vector2f& v);

std::ostream& operator<<(std::ostream& stream, const sf::FloatRect& v);
#endif
