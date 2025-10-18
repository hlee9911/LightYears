#include "weapon/Shooter.h"

namespace ly
{
	void Shooter::Shoot()
	{
		if (CanShoot() && !IsOnCooldown())
		{
			ShootImpl();
		}
	}

	void Shooter::IncrementLevel(int amt)
	{
		if (m_CurrentLevel == m_MaxLevel) return;
		++m_CurrentLevel;
	}

	Shooter::Shooter(Actor* owner) noexcept
		: m_Owner{ owner },
		m_CurrentLevel{ 1 },
		m_MaxLevel{ 4 }
	{

	}
}
