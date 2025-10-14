#pragma once
#ifndef UFO_H
#define UFO_H

#include "enemy/EnemySpaceship.h"

namespace ly
{
	class BulletShooter;
	class UFO : public EnemySpaceship
	{
	public:
		UFO(World* owningWorld, const sf::Vector2f& velocity, const std::string& texturePath = "SpaceShooterRedux/PNG/ufoBlue.png", float rotatingSpeed = 40.0f) noexcept;
		virtual void Tick(float deltaTime) override;

	private:
		virtual void Shoot() override;

	private:
		unique<BulletShooter> m_Shooter0;
		unique<BulletShooter> m_Shooter1;
		unique<BulletShooter> m_Shooter2;
		float m_Rotationspeed;

	};
}

#endif // UFO_H
