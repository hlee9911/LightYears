#pragma once
#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <string>

#include "framework/Actor.h"

namespace ly
{
	class Spaceship : public Actor
	{
	public:
		Spaceship(World* owningWorld, const std::string& texturePath = "") noexcept;
		virtual void Tick(float deltaTime) override;

		void SetVelocity(const sf::Vector2f& newVel) noexcept;
		sf::Vector2f GetVelocity() const noexcept { return m_Velocity; }

	private:
		sf::Vector2f m_Velocity;
	};
}

#endif // SPACESHIP_H
