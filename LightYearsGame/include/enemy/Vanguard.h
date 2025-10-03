#pragma once
#ifndef VANGUARD_H
#define	VANGUARD_H

#include "enemy/EnemySpaceship.h"

namespace ly
{
	class BulletShooter;
	class Vanguard : public EnemySpaceship
	{
	public:
		Vanguard(World* owningWorld, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlue3.png", const sf::Vector2f& velocity = { 0.0f, 50.0f }) noexcept;
		virtual void Tick(float deltaTime) override;

	private:
		virtual void Shoot() override;

	private:
		unique<BulletShooter> m_Shooter;
	};
}


#endif // VANGUARD_H
