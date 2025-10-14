#include "enemy/Hexagon.h"
#include "weapon/BulletShooter.h"

namespace ly
{
	Hexagon::Hexagon(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity) noexcept
		: EnemySpaceship{ owningWorld, texturePath },
		m_Shooter0{ new BulletShooter{this, 1.0f, sf::Vector2f{20.0f, 50.0f}, 30.0f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		m_Shooter1{ new BulletShooter{this, 1.0f, sf::Vector2f{20.0f, -50.0f}, -30.0f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		m_Shooter2{ new BulletShooter{this, 1.0f, sf::Vector2f{50.0f, 0.0f}, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		m_Shooter3{ new BulletShooter{this, 1.0f, sf::Vector2f{-50.0f, 0.0f}, -180.0f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		m_Shooter4{ new BulletShooter{this, 1.0f, sf::Vector2f{-20.0f, 50.0f}, 120.0f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		m_Shooter5{ new BulletShooter{this, 1.0f, sf::Vector2f{-20.0f, -50.0f}, -120.0f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} }
	{
		SetVelocity(velocity);
		SetActorRotation(180.0f);
	}

	void Hexagon::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);

		Shoot();
	}

	void Hexagon::Shoot()
	{
		m_Shooter0->Shoot();
		m_Shooter1->Shoot();
		m_Shooter2->Shoot();
		m_Shooter3->Shoot();
		m_Shooter4->Shoot();
		m_Shooter5->Shoot();
	}
}
