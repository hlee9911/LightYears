#pragma once
#ifndef MATHUTILITY_H
#define MATHUTILITY_H

#include <SFML/Graphics.hpp>

namespace ly
{
	sf::Vector2f RotationToVector(float rotation);
	float DegreesToRadians(float degrees);
	float RadiansToDegrees(float radians);

	// Get magnitude of a vector
	template<typename T>
	float GetVectorLength(sf::Vector2<T>& vctor)
	{
		return std::sqrt(vctor.x * vctor.x + vctor.y * vctor.y);
	}

	// Scale a vector by amt
	template<typename T>
	sf::Vector2<T>& ScaleVector(sf::Vector2<T>& vectorToScale, float amt)
	{
		vectorToScale.x *= amt;
		vectorToScale.y *= amt;
		return vectorToScale;
	}

	// Normalize a vector
	template<typename T>
	sf::Vector2<T>& NormalizeVector(sf::Vector2<T>& vector)
	{
		float vectorLength = GetVectorLength<T>(vector);
		if (vectorLength == 0.0f) return sf::Vector2<T>{};
		ScaleVector(vector, 1.0f / vectorLength);
		return vector;
	}

	sf::Color LerpColor(const sf::Color& a, const sf::Color& b, float alpha);

	sf::Vector2f LerpVector(const sf::Vector2f& a, const sf::Vector2f& b, float alpha);
	
	float LerpFloat(float a, float b, float alpha);

	float RandomRange(float min, float max);
	
	sf::Vector2f RandomUnitVector();
}

#endif // MATHUTILITY_H
