#pragma once
#ifndef MATHUTILITY_H
#define MATHUTILITY_H

#include <SFML/Graphics.hpp>

namespace ly
{
	sf::Vector2f RotationToVector(float rotation);
	float DegreesToRadians(float degrees);
	float RadiansToDegrees(float radians);
}

#endif // MATHUTILITY_H
