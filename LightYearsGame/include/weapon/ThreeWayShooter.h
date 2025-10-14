#pragma once
#ifndef THREEWAYSHOOTER_H
#define THREEWAYSHOOTER_H

// #include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "weapon/BulletShooter.h"

namespace ly
{
	class ThreeWayShooter : public Shooter
	{
	public:
		ThreeWayShooter(Actor* owner, float cooldownTime = 0.3f, 
			const sf::Vector2f& localOffset = { 0.0f,0.0f }) noexcept;

	private:
		virtual void ShootImpl() override;

	private:
		BulletShooter m_ShooterLeft;
		BulletShooter m_ShooterMid;
		BulletShooter m_ShooterRight;

	};
}

#endif //THREEWAYSHOOTER_H
