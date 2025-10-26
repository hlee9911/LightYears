#include "weapon/FrontalWiper.h"

namespace ly
{
	FrontalWiper::FrontalWiper(Actor* owner, float cooldownTime, const sf::Vector2f& localOffset, float width) noexcept
		: Shooter{ owner },
		m_Width{ width },
		m_Shooter0{ owner, cooldownTime, {localOffset.x, localOffset.y - width / 2.0f}, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" },
		m_Shooter1{ owner, cooldownTime, {localOffset.x, localOffset.y - width / 6.0f}, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png" },
		m_Shooter2{ owner, cooldownTime, {localOffset.x, localOffset.y + width / 6.0f}, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png" },
		m_Shooter3{ owner, cooldownTime, {localOffset.x, localOffset.y + width / 2.0f}, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" },
		m_Shooter4{ owner, cooldownTime / 1.5f, {localOffset.x, localOffset.y + width / 1.5f}, 10.0f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png" },
		m_Shooter5{ owner, cooldownTime / 1.5f, {localOffset.x, localOffset.y - width / 1.5f}, -10.0f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png" }
	{

	}

	void FrontalWiper::IncrementLevel(int amt)
	{
		Shooter::IncrementLevel(amt);

		m_Shooter0.IncrementLevel(amt);
		m_Shooter1.IncrementLevel(amt);
		m_Shooter2.IncrementLevel(amt);
		m_Shooter3.IncrementLevel(amt);
		m_Shooter4.IncrementLevel(amt);
		m_Shooter5.IncrementLevel(amt);
	}

	void FrontalWiper::SetCurrentLevel(int level) noexcept
	{
		Shooter::SetCurrentLevel(level);

		m_Shooter0.SetCurrentLevel(level);
		m_Shooter1.SetCurrentLevel(level);
		m_Shooter2.SetCurrentLevel(level);
		m_Shooter3.SetCurrentLevel(level);
		m_Shooter4.SetCurrentLevel(level);
		m_Shooter5.SetCurrentLevel(level);
	}

	void FrontalWiper::ShootImpl()
	{
		m_Shooter0.Shoot();
		m_Shooter1.Shoot();
		m_Shooter2.Shoot();
		m_Shooter3.Shoot();

		if (GetCurrentLevel() == GetMaxLevel())
		{
			m_Shooter4.Shoot();
			m_Shooter5.Shoot();
		}
	}
}
