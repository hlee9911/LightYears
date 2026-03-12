#pragma once

#include "enemy/EnemySpaceship.h"

namespace ly
{
	class BulletShooter;
	class TwinBlade : public EnemySpaceship
	{
	public:

		TwinBlade(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlack1.png", const sf::Vector2f& velocity = { 0.0f, 150.0f }) noexcept;
		virtual void Tick(float deltaTime) override;

	private:

		virtual void Shoot() override;

	private:
		unique<BulletShooter> m_ShooterLeft;
		unique<BulletShooter> m_ShooterRight;
	};
}
