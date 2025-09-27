#include "spaceship/Spaceship.h"

// #include <functional>

namespace ly
{
	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath) noexcept
		: Actor{ owningWorld, texturePath },
		m_Velocity{},
		m_HealthComp{ 100.0f, 100.0f }
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

		//float damage = -10.0f;
		//// Example usage of lambda function, [] is the capture list. & means capture by reference, = means capture by value
		//std::function<void(float)> func = [damage](float var)
		//{
		//	LOG("Stuff %f", var);
		//};

		//func(5.0f);

		m_HealthComp.onHealthChanged.BindAction(GetWeakRef(), &Spaceship::OnHealthChanged);
	}

	void Spaceship::OnHealthChanged(float amt, float health, float maxHealth)
	{

	}
}
