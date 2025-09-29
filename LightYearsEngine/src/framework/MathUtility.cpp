#include "framework/MathUtility.h"

#include <random>

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

	/// <summary>
	/// This function performs linear interpolation between two colors a and b based on the alpha parameter.
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <param name="alpha"></param>
	/// <returns></returns>
	sf::Color LerpColor(const sf::Color& a, const sf::Color& b, float alpha)
	{
		int lerpR = LerpFloat(a.r, b.r, alpha);
		int lerpG = LerpFloat(a.g, b.g, alpha);
		int lerpB = LerpFloat(a.b, b.b, alpha);
		int lerpA = LerpFloat(a.a, b.a, alpha);

		return sf::Color(lerpR, lerpG, lerpB, lerpA);
	}

	/// <summary>
	/// This function performs linear interpolation between two 2D vectors a and b based on the alpha parameter.
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <param name="alpha"></param>
	/// <returns></returns>
	sf::Vector2f LerpVector(const sf::Vector2f& a, const sf::Vector2f& b, float alpha)
	{
		float lerpX = LerpFloat(a.x, b.x, alpha);
		float lerpY = LerpFloat(a.y, b.y, alpha);
		return sf::Vector2f(lerpX, lerpY);
	}

	/// <summary>
	/// This function performs linear interpolation between two float values a and b based on the alpha parameter.
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <param name="alpha"></param>
	/// <returns></returns>
	float LerpFloat(float a, float b, float alpha)
	{
		if (alpha > 1.0f) alpha = 1.0f;
		if (alpha < 0.0f) alpha = 0.0f;

		return a + (b - a) * alpha;
	}

	/// <summary>
	/// This function generates a random floating-point number between the specified minimum (min) and maximum (max) values.
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	float RandomRange(float min, float max)
	{
		std::random_device rd;  // Obtain a random number from hardware
		std::mt19937 gen(rd()); // Seed the generator

		std::uniform_real_distribution<float> distribution{ min, max }; // Define the range

		return distribution(gen); // Generate the random number
	}

	sf::Vector2f RandomUnitVector()
	{
		float randomX = RandomRange(-1.0f, 1.0f);
		float randomY = RandomRange(-1.0f, 1.0f);
		sf::Vector2f randomVector{ randomX, randomY };
		NormalizeVector(randomVector);
		return randomVector;
	}
}

