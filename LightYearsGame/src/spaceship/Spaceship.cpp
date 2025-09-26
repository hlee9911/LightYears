#include "spaceship/Spaceship.h"

namespace ly
{
	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath) noexcept
		: Actor{ owningWorld, texturePath },
		m_Velocity{}
	{
		
	}

	void Spaceship::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		// Move the spaceship based on its velocity
		AddActorLocationOffset(GetVelocity() * deltaTime);
	}

	void Spaceship::SetVelocity(const sf::Vector2f& newVel) noexcept
	{
		m_Velocity = newVel;
	}

	void Spaceship::Shoot()
	{

	}

	void Spaceship::BeginPlay()
	{
		Actor::BeginPlay();
		
		SetEnablePhysics(true);
	}
}
