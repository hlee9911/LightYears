#include "enemy/EnemySpaceship.h"

namespace ly
{
	EnemySpaceship::EnemySpaceship(World* owningWorld, const std::string& texturePath, float collisionDamage) noexcept
		: Spaceship{ owningWorld, texturePath },
		m_CollisionDamage{ collisionDamage }
	{
		SetTeamID(2); // Enemy team ID is 2
	}

	void EnemySpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);

		if (IsActorOutOfWindowsBounds(GetActorGlobalBounds().width))
		{
			Destroy();
		}
	}

	void EnemySpaceship::OnActorBeginOverlap(Actor* otherActor)
	{
		Spaceship::OnActorBeginOverlap(otherActor);

		if (IsOtherHostile(otherActor))
		{
			otherActor->ApplyDamage(m_CollisionDamage);
		}
	}
}
