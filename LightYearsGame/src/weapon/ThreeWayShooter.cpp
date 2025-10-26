#include "weapon/ThreeWayShooter.h"

namespace ly
{
	ThreeWayShooter::ThreeWayShooter(Actor* owner, float cooldownTime, const sf::Vector2f& localOffset) noexcept
		: Shooter{ owner },
		m_ShooterLeft{ owner, cooldownTime, localOffset + sf::Vector2f{10.0f, -10.0f}, -30.0f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" },
		m_ShooterMid{ owner, cooldownTime, localOffset, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" },
		m_ShooterRight{ owner, cooldownTime, localOffset + sf::Vector2f{10.0f, 10.0f}, 30.0f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" },
		m_TopLevelShooterLeft{ owner, cooldownTime, localOffset + sf::Vector2f{10.0f, 10.0f}, 15.0f, "SpaceShooterRedux/PNG/Lasers/laserBlue01.png" },
		m_TopLevelShooterRight{ owner, cooldownTime, localOffset + sf::Vector2f{10.0f, -10.0f}, -15.0f, "SpaceShooterRedux/PNG/Lasers/laserBlue01.png" }
	{

	}

	void ThreeWayShooter::IncrementLevel(int amt)
	{
		Shooter::IncrementLevel(amt);

		m_ShooterLeft.IncrementLevel(amt);
		m_ShooterMid.IncrementLevel(amt);
		m_ShooterRight.IncrementLevel(amt);

		m_TopLevelShooterLeft.IncrementLevel(amt);
		m_TopLevelShooterRight.IncrementLevel(amt);
	}

	void ThreeWayShooter::SetCurrentLevel(int level) noexcept
	{
		Shooter::SetCurrentLevel(level);

		m_ShooterLeft.SetCurrentLevel(level);
		m_ShooterMid.SetCurrentLevel(level);
		m_ShooterRight.SetCurrentLevel(level);

		m_TopLevelShooterLeft.SetCurrentLevel(level);
		m_TopLevelShooterRight.SetCurrentLevel(level);
	}

	void ThreeWayShooter::ShootImpl()
	{
		m_ShooterLeft.Shoot();
		m_ShooterMid.Shoot();
		m_ShooterRight.Shoot();

		if (GetCurrentLevel() == GetMaxLevel())
		{
			m_TopLevelShooterLeft.Shoot();
			m_TopLevelShooterRight.Shoot();
		}
	}


}
