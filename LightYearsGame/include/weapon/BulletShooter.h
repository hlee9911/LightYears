#pragma once
#ifndef BULLETSHOOTER_H
#define BULLETSHOOTER_H

#include <SFML/System.hpp>
#include <string>

#include "weapon/Shooter.h"

namespace ly
{
	class BulletShooter : public Shooter
	{
	public:
		BulletShooter(Actor* owner,
			float cooldownTime = 1.0f,
			const sf::Vector2f& localPositionOffset = { 0.0f, 0.0f },
			float localRotationOffset = 0.0f,
			const std::string& bulletTexturePath = "SpaceShooterRedux/PNG/Lasers/laserBlue01.png") noexcept;

		virtual bool CanShoot() const override;
		virtual bool IsOnCooldown() const override;

		void SetBulletTexturePath(const std::string& bulletTexturePath) noexcept;

	private:
		virtual void ShootImpl() override;

	private:
		sf::Clock m_CooldownClock;
		float m_CooldownTime;
		sf::Vector2f m_LocalPositionOffset;
		float m_LocalRotationOffset;
		std::string m_BulletTexturePath;
	};
}

#endif // BULLETSHOOTER_H
