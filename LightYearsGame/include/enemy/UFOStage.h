#pragma once
#ifndef UFOSTAGE_H
#define UFOSTAGE_H

#include <SFML/Graphics.hpp>

#include "gameplay/GameStage.h"
#include "framework/TimerManager.h"

namespace ly
{
	class UFOStage : public GameStage
	{
	public:
		UFOStage(World* owningWorld) noexcept;

		virtual void StartStage() override;

	private:
		virtual void StageFinished() override;
		sf::Vector2f GetRandomSpawnLoc() const;
		void SpawnUFO();

	private:
		float m_SpawnInterval;
		int m_SpawnAmt;
		int m_CurrentSpawnAmt;
		float m_UFOSpeed;

		TimerHandle m_SpawnTimerHandle;
	};
}

#endif // UFOSTAGE_H
