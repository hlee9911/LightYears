#pragma once
#ifndef CHAOSSTAGE_H
#define CHAOSSTAGE_H

#include <SFML/Graphics.hpp>

#include "gameplay/GameStage.h"
#include "framework/TimerManager.h"

namespace ly
{
	class ChaosStage : public GameStage
	{
	public:
		ChaosStage(World* owningWorld) noexcept;

		virtual void StartStage() override;

	private:
		virtual void StageFinished() override;
		void SpawnVanguard();
		void SpawnTwinBlade();
		void SpawnHexagon();
		void SpawnUFO();

		void IncreaseDifficulty();
		void StageDurationReached();

		sf::Vector2f GetRandomSpawnLocationTop() const;
		sf::Vector2f GetRandomSpawnLocationSide() const;

	private:
		float m_SpawnInterval;
		float m_MinSpawnInterval;

		float m_SpawnIntervalDecrement;
		// for every period of time, we reduce the spawn interval by m_SpawnIntervalDecrement
		float m_SpawnIntervalDecrementInterval;

		float m_StageDuration;
		
		TimerHandle m_DifficultTimerHandle;
		TimerHandle m_SpawnTimerHandle;
	};
}

#endif // CHAOSSTAGE_H
