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

		m_HealthComp.onHealthChanged.BindAction(GetWeakRef(), &Spaceship::OnHealthChanged);
		m_HealthComp.onTakenDamage.BindAction(GetWeakRef(), &Spaceship::OnTakenDamage);
		m_HealthComp.onHealthEmpty.BindAction(GetWeakRef(), &Spaceship::OnBlow);
	}

	void Spaceship::ApplyDamage(float damageAmt)
	{
		m_HealthComp.ChangeHealth(-damageAmt);
	}

	void Spaceship::OnHealthChanged(float amt, float health, float maxHealth)
	{
		LOG("Spaceship Health Changed by %f, Current Health: %f/%f", amt, health, maxHealth);
	}

	void Spaceship::OnTakenDamage(float amt, float health, float maxHealth)
	{

	}

	void Spaceship::OnBlow()
	{
		Destroy();
	}
}
