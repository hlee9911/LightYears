#include "weapon/FrontalWiper.h"

namespace ly
{
	FrontalWiper::FrontalWiper(Actor* owner, float cooldownTime, const sf::Vector2f& localOffset, float width) noexcept
		: Shooter{ owner },
		m_Width{ width },
		m_Shooter0{ owner, cooldownTime, {localOffset.x, localOffset.y - width / 2.0f}, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" },
		m_Shooter1{ owner, cooldownTime, {localOffset.x, localOffset.y - width / 6.0f}, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png" },
		m_Shooter2{ owner, cooldownTime, {localOffset.x, localOffset.y + width / 6.0f}, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png" },
		m_Shooter3{ owner, cooldownTime, {localOffset.x, localOffset.y + width / 2.0f}, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" }
	{

	}

	void FrontalWiper::ShootImpl()
	{
		m_Shooter0.Shoot();
		m_Shooter1.Shoot();
		m_Shooter2.Shoot();
		m_Shooter3.Shoot();
	}
}
