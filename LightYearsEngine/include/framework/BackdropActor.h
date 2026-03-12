#pragma once

#include "framework/Actor.h"

#include <string>

namespace ly
{
	class BackdropActor : public Actor
	{
	public:
		BackdropActor(World* owningWorld, 
			const std::string& texturePath, 
			const sf::Vector2f& velocity = sf::Vector2f{0.0f, -125.0f}) noexcept;

		virtual void Tick(float deltaTime) override;

	private:
		sf::Vector2f m_MovingVelocity;
		float m_LeftShift;
		float m_TopShift;
	};
}
