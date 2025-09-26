#include "weapon/Bullet.h"

namespace ly
{
	Bullet::Bullet(World* world, Actor* owner, const std::string& texturePath, float speed, float damage) noexcept
		: Actor{ world, texturePath },
		m_Owner{ owner },
		m_Speed{ speed },
		m_Damage{ damage }
	{

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

	void Bullet::Move(float deltaTime)
	{
		AddActorLocationOffset(GetActorForwardDirection() * m_Speed * deltaTime);
	}

}
