#include "weapon/Bullet.h"

namespace ly
{
	Bullet::Bullet(World* world, Actor* owner, const std::string& texturePath, float speed, float damage) noexcept
		: Actor{ world, texturePath },
		m_Owner{ owner },
		m_Speed{ speed },
		m_Damage{ damage }
	{
		SetTeamID(owner->GetTeamID()); // Inherit team ID from owner of the bullet
	}

	void Bullet::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		Move(deltaTime);

		if (IsActorOutOfWindowsBounds())
		{
			Destroy();
		}
	}

	void Bullet::BeginPlay()
	{
		Actor::BeginPlay();

		SetEnablePhysics(true);
	}

	void Bullet::Move(float deltaTime)
	{
		AddActorLocationOffset(GetActorForwardDirection() * m_Speed * deltaTime);
	}

	void Bullet::OnActorBeginOverlap(Actor* otherActor)
	{
		if (IsOtherHostile(otherActor))
		{
			// Apply damage to the other actor if it has a health component
			otherActor->ApplyDamage(GetDamage());
			Destroy(); // Destroy the bullet after hitting a hostile actor
		}
	}

}
