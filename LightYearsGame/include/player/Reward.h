#pragma once
#ifndef REWARD_H
#define REWARD_H

#include "framework/Actor.h"

#include <functional>
#include <string>

namespace ly
{
	class PlayerSpaceship;
	class Reward;
	using RewardFunc = std::function<void(PlayerSpaceship*)>;
	using RewardFactoryFunc = std::function<weak<Reward>(World*)>;

	class Reward : public Actor
	{
	public:
		Reward(World* owningWorld, const std::string& texturePath, RewardFunc rewardFunc, float speed = 200.0f) noexcept;
		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;

	private:
		virtual void OnActorBeginOverlap(Actor* otherActor) override;

	private:
		float m_Speed;
		RewardFunc m_RewardFunc;
	};

	weak<Reward> CreateHealthReward(World* world);
	weak<Reward> CreateThreeWayShooterReward(World* world);
	weak<Reward> CreateFrontalWiperReward(World* world);
	weak<Reward> CreateLifeUpReward(World* world);

	// Factory function to create actual corresponding reward based enemy holding the reward
	weak<Reward> CreateReward(World* world, const std::string& texturePath, RewardFunc rewardFunc);

	void RewardHealth(PlayerSpaceship* player);
	void RewardThreewayShooter(PlayerSpaceship* player);
	void RewardFrontalWiper(PlayerSpaceship* player);
	void RewardLifeUp(PlayerSpaceship* player);
}

#endif // REWARD_H
