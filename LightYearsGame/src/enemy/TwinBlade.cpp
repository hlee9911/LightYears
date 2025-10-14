#include "enemy/TwinBlade.h"
#include "weapon/BulletShooter.h"

namespace ly
{
	TwinBlade::TwinBlade(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity) noexcept
		: EnemySpaceship{ owningWorld, texturePath },
		m_ShooterLeft{ new BulletShooter{this, 1.0f, {50.0f, 20.0f}, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		m_ShooterRight{ new BulletShooter{this, 1.0f, {50.0f, -20.0f}, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} }
	{
		SetVelocity(velocity);
		SetActorRotation(180.0f);
	}

	void TwinBlade::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);

		Shoot();
	}

	void TwinBlade::Shoot()
	{
		m_ShooterLeft->Shoot();
		m_ShooterRight->Shoot();
	}

}
