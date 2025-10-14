#include "enemy/UFO.h"
#include "weapon/BulletShooter.h"

namespace ly
{
	UFO::UFO(World* owningWorld, const sf::Vector2f& velocity, const std::string& texturePath, float rotatingSpeed) noexcept
		: EnemySpaceship{ owningWorld, texturePath },
		m_Shooter0{ new BulletShooter{this, 0.5f, sf::Vector2f{0.0f, 0.0f}, -60.0f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		m_Shooter1{ new BulletShooter{this, 0.5f, sf::Vector2f{0.0f, 0.0f}, 60.0f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		m_Shooter2{ new BulletShooter{this, 0.5f, sf::Vector2f{0.0f, 0.0f}, 180.0f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		m_Rotationspeed{ rotatingSpeed }
	{
		SetVelocity(velocity);
		SetActorRotation(180.0f);
	}
	
	void UFO::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);

		Shoot();
		AddActorRotationOffset(m_Rotationspeed * deltaTime);
	}

	void UFO::Shoot()
	{
		m_Shooter0->Shoot();
		m_Shooter1->Shoot();
		m_Shooter2->Shoot();
	}
}
