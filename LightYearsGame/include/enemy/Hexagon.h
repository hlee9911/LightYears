#pragma once

#include "enemy/EnemySpaceship.h"

namespace ly
{
	class BulletShooter;
	class Hexagon : public EnemySpaceship
	{
	public:
		Hexagon(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyGreen4.png", const sf::Vector2f& velocity = { 0.0f, 125.0f }) noexcept;
		virtual void Tick(float deltaTime) override;

	private:
		virtual void Shoot() override;

	private:
		unique<BulletShooter> m_Shooter0;
		unique<BulletShooter> m_Shooter1;
		unique<BulletShooter> m_Shooter2;
		unique<BulletShooter> m_Shooter3;
		unique<BulletShooter> m_Shooter4;
		unique<BulletShooter> m_Shooter5;
	};
}
