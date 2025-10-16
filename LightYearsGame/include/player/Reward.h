#pragma once
#ifndef REWARD_H
#define REWARD_H

#include "framework/Actor.h"

#include <functional>
#include <string>

namespace ly
{
	class PlayerSpaceship;
	using RewardFunc = std::function<void(PlayerSpaceship*)>;
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
}

#endif // REWARD_H
