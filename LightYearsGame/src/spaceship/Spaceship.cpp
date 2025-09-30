#include "spaceship/Spaceship.h"
#include "framework/MathUtility.h"
#include "VFX/Explosion.h"

// #include <functional>

namespace ly
{
	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath) noexcept
		: Actor{ owningWorld, texturePath },
		m_Velocity{},
		m_HealthComp{ 100.0f, 100.0f },
		m_BlinkTime{ 0.0f },
		m_BlinkDuration{ 0.2f },
		m_BlinkColorOffset{ 255, 0, 0, 255 }
	{
		
	}

	void Spaceship::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		// Move the spaceship based on its velocity
		AddActorLocationOffset(GetVelocity() * deltaTime);

		// Update blinking effect if taking damage
		UpdateBlink(deltaTime);
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

	/// <summary>
	/// This function initiates the blinking effect of the spaceship when it takes damage.
	/// </summary>
	void Spaceship::Blink()
	{
		if (m_BlinkTime == 0.0f)
		{
			m_BlinkTime = m_BlinkDuration;
		}
	}

	/// <summary>
	/// This function updates the blinking effect of the spaceship when it takes damage.
	/// </summary>
	/// <param name="deltaTime"></param>
	void Spaceship::UpdateBlink(float deltaTime)
	{
		if (m_BlinkTime > 0.0f)
		{
			m_BlinkTime -= deltaTime;
			m_BlinkTime = m_BlinkTime > 0.0f ? m_BlinkTime : 0.0f;

			GetSprite().setColor(LerpColor(sf::Color::White, m_BlinkColorOffset, m_BlinkTime));
		}
	}

	void Spaceship::OnHealthChanged(float amt, float health, float maxHealth)
	{
		LOG("Spaceship Health Changed by %f, Current Health: %f / %f", amt, health, maxHealth);
	}

	void Spaceship::OnTakenDamage(float amt, float health, float maxHealth)
	{
		Blink();
	}

	void Spaceship::OnBlow()
	{
		Explosion* exp = new Explosion();
		exp->SpawnExplosion(GetWorld(), GetActorLocation());
		Destroy();
		delete exp;
	}
}
