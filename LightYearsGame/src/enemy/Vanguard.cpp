#include "enemy/Vanguard.h"
#include "weapon/BulletShooter.h"

namespace ly
{
	Vanguard::Vanguard(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity) noexcept
		: EnemySpaceship{ owningWorld, texturePath },
		m_Shooter{ new BulletShooter{this, 1.0f, {50.0f, 0.0f}, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} }
	{
		SetVelocity(velocity);
		SetActorRotation(180.0f);
	}

	void Vanguard::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
	}

	void Vanguard::Shoot()
	{
		m_Shooter->Shoot();
	}

}
