#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "framework/Core.h"

namespace ly
{
	class World;
	/// <summary>
	/// This class represents an explosion effect that spawns multiple particles with random properties.
	/// </summary>
	class Explosion
	{
	public:
		Explosion(int particleAmt = 20, 
			float lifeTimeMin = 0.5f,
			float lifeTimeMax = 1.5f,
			float sizeMin = 1.0f,
			float sizeMax = 3.0f,
			float speedMin = 200.0f,
			float speedMax = 400.0f,
			const sf::Color& particleColor = sf::Color{ 255, 128, 0, 255 },
			const List<std::string>& particleImagePaths = 
			{ 
				"SpaceShooterRedux/PNG/Effects/star1.png",
				"SpaceShooterRedux/PNG/Effects/star2.png",
				"SpaceShooterRedux/PNG/Effects/star3.png" 
			}
		) noexcept;

		void SpawnExplosion(World* owningWorld, const sf::Vector2f& location);

	private:
		int m_ParticleAmt;
		float m_LifetimeMin;
		float m_LifetimeMax;
		float m_SizeMin;
		float m_SizeMax;
		float m_SpeedMin;
		float m_SpeedMax;

		sf::Color m_ParticleColor;
		List<std::string> m_ParticleImagePaths;
	};
}
