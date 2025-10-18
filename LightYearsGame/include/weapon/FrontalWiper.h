#pragma once
#ifndef FRONTALWIPER_H
#define FRONTALWIPER_H

#include <SFML/System.hpp>

#include "weapon/BulletShooter.h"

namespace ly
{
	class FrontalWiper : public Shooter
	{
	public:
		FrontalWiper(Actor* owner, 
			float cooldownTime = 0.5f,
			const sf::Vector2f& localOffset = { 0.0f,0.0f },
			float width = 60.0f) noexcept;

		virtual void IncrementLevel(int amt = 1) override;

	private:
		virtual void ShootImpl() override;

	private:
		BulletShooter m_Shooter0;
		BulletShooter m_Shooter1;
		BulletShooter m_Shooter2;
		BulletShooter m_Shooter3;

		BulletShooter m_Shooter4;
		BulletShooter m_Shooter5;

		float m_Width;
	};
}

#endif // FRONTALWIPER_H
