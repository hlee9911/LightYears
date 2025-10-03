#pragma once
#ifndef ENEMYSPACESHIP_H
#define ENEMYSPACESHIP_H

#include "spaceship/Spaceship.h"

namespace ly
{
	class EnemySpaceship : public Spaceship
	{
	public:
		EnemySpaceship(World* owningWorld, const std::string& texturePath, float collisionDamage = 200.0f) noexcept;

		virtual void Tick(float deltaTime) override;

	private:
		virtual void OnActorBeginOverlap(Actor* otherActor) override;

	private:
		float m_CollisionDamage;

	};
}

#endif // ENEMYSPACESHIP_H
