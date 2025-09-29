#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H

#include <string>

#include "framework/Actor.h"

namespace ly
{
	class Particle : public Actor
	{
	public:
		Particle(World* owningWorld, const std::string& texturePath) noexcept;

		virtual void Tick(float deltaTime) override;

		void RandomVelocity(float minSpeed, float maxSpeed);
		void RandomSize(float minSize, float maxSize);
		void RandomLifetime(float minLifetime, float maxLifetime);

	private:
		void Move(float deltaTime);
		void Fade(float deltaTime);

	private:
		sf::Vector2f m_Velocity;
		float m_Lifetime;
		sf::Clock m_Timer;

	};
}

#endif // PARTICLE_H
