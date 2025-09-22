#include "framework/MathUtility.h"

namespace ly
{
	constexpr float PI = 3.14159265358979323846f;

	sf::Vector2f RotationToVector(float rotation)
	{
		float radians = DegreesToRadians(rotation);
		return sf::Vector2f(std::cos(radians), std::sin(radians));
	}

	float DegreesToRadians(float degrees)
	{
		return degrees * (PI / 180.0f);
	}

	float RadiansToDegrees(float radians)
	{
		return radians * (180.0f / PI);
	}
}

