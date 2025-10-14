#include "weapon/ThreeWayShooter.h"

namespace ly
{
	ThreeWayShooter::ThreeWayShooter(Actor* owner, float cooldownTime, const sf::Vector2f& localOffset) noexcept
		: Shooter{ owner },
		m_ShooterLeft{ owner, cooldownTime, localOffset + sf::Vector2f{10.0f, -10.0f}, -30.0f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" },
		m_ShooterMid{ owner, cooldownTime, localOffset, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" },
		m_ShooterRight{ owner, cooldownTime, localOffset + sf::Vector2f{10.0f, 10.0f}, 30.0f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" }
	{

	}

	void ThreeWayShooter::ShootImpl()
	{
		m_ShooterLeft.Shoot();
		m_ShooterMid.Shoot();
		m_ShooterRight.Shoot();
	}


}
