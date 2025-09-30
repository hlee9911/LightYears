#include "VFX/Explosion.h"
#include "VFX/Particle.h"
#include "framework/MathUtility.h"
#include "framework/World.h"

namespace ly
{
	Explosion::Explosion(int particleAmt, float lifeTimeMin, float lifeTimeMax, float sizeMin, float sizeMax, float speedMin, float speedMax, const sf::Color& particleColor, const List<std::string>& particleImagePaths) noexcept
		: m_ParticleAmt{ particleAmt },
		m_LifetimeMin{ lifeTimeMin },
		m_LifetimeMax{ lifeTimeMax },
		m_SizeMin{ sizeMin },
		m_SizeMax{ sizeMax },
		m_SpeedMin{ speedMin },
		m_SpeedMax{ speedMax },
		m_ParticleColor{ particleColor },
		m_ParticleImagePaths{ particleImagePaths }
	{

	}

	/// <summary>
	/// This function spawns an explosion effect at the specified location in the given world.
	/// </summary>
	/// <param name="owningWorld"></param>
	/// <param name="location"></param>
	void Explosion::SpawnExplosion(World* owningWorld, const sf::Vector2f& location)
	{
		if (!owningWorld) return;
		
		for (int i = 0; i < m_ParticleAmt; ++i)
		{
			std::string particleImagePath = m_ParticleImagePaths[(int)RandomRange(0, m_ParticleImagePaths.size())];
			weak<Particle> newParticle = owningWorld->SpawnActor<Particle>(particleImagePath);

			newParticle.lock()->RandomLifetime(m_LifetimeMin, m_LifetimeMax);
			newParticle.lock()->SetActorLocation(location);
			newParticle.lock()->RandomSize(m_SizeMin, m_SizeMax);
			newParticle.lock()->RandomVelocity(m_SpeedMin, m_SpeedMax);
			newParticle.lock()->GetSprite().setColor(m_ParticleColor);
		}
	}
}
