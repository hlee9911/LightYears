#include "VFX/Particle.h"
#include "framework/MathUtility.h"

namespace ly
{
	Particle::Particle(World* owningWorld, const std::string& texturePath) noexcept
		: Actor{ owningWorld, texturePath },
		m_Velocity{},
		m_Lifetime{ 1.0f },
		m_Timer{}
	{

	}

	void Particle::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		
		Move(deltaTime);
		Fade(deltaTime);

		if (m_Timer.getElapsedTime().asSeconds() >= m_Lifetime)
		{
			Destroy();
		}
	}

	void Particle::RandomVelocity(float minSpeed, float maxSpeed)
	{
		m_Velocity = RandomUnitVector() * RandomRange(minSpeed, maxSpeed);
	}

	void Particle::RandomSize(float minSize, float maxSize)
	{
		float randScale = RandomRange(minSize, maxSize);
		GetSprite().setScale(randScale, randScale);
	}

	void Particle::RandomLifetime(float minLifetime, float maxLifetime)
	{
		m_Lifetime = RandomRange(minLifetime, maxLifetime);
	}

	void Particle::Move(float deltaTime)
	{
		AddActorLocationOffset(m_Velocity * deltaTime);
	}

	void Particle::Fade(float deltaTime)
	{
		float elapsedTime = m_Timer.getElapsedTime().asSeconds();
		GetSprite().setColor(LerpColor(GetSprite().getColor(), sf::Color(255, 255, 255, 0), elapsedTime / m_Lifetime));
		GetSprite().setScale(LerpVector(GetSprite().getScale(), sf::Vector2f{0.0f, 0.0f}, elapsedTime / m_Lifetime));
	}

}
