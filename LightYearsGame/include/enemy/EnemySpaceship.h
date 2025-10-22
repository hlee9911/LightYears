#pragma once
#ifndef ENEMYSPACESHIP_H
#define ENEMYSPACESHIP_H

#include "spaceship/Spaceship.h"
#include "player/Reward.h"

namespace ly
{
	class EnemySpaceship : public Spaceship
	{
	public:
		EnemySpaceship(World* owningWorld, 
			const std::string& texturePath, 
			float collisionDamage = 200.0f,
			float rewardDropWeight = 0.50f,
			const List<RewardFactoryFunc> rewards = 
			{
				CreateHealthReward,
				CreateThreeWayShooterReward,
				CreateFrontalWiperReward,
				CreateLifeUpReward
			}
		) noexcept;

		virtual void Tick(float deltaTime) override;
		void SetScoreAwardAmount(unsigned int amount) noexcept { m_ScoreAwardAmt = amount; }

	private:
		void SpawnReward();
		virtual void OnActorBeginOverlap(Actor* otherActor) override;
		virtual void Blew() override;

	private:
		float m_CollisionDamage;
		List<RewardFactoryFunc> m_RewardFactories;
		unsigned int m_ScoreAwardAmt;
		float m_RewardDropWeight;
	};
}

#endif // ENEMYSPACESHIP_H
