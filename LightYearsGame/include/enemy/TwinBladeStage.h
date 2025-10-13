#pragma once
#ifndef TWINBLADESTAGE_H
#define TWINBLADESTAGE_H

#include <SFML/Graphics.hpp>

#include "gameplay/GameStage.h"
#include "framework/TimerManager.h"

namespace ly
{
	class TwinBladeStage : public GameStage
	{
	public:
		TwinBladeStage(World* owningWorld) noexcept;

		virtual void StartStage() override;

	private:
		virtual void StageFinished() override;
		void SpawnTwinBlade();

	private:
		float m_SpawnInterval;
		float m_SpawnDistanceToCenter;

		sf::Vector2f m_LeftSpawnLoc;
		sf::Vector2f m_RightSpawnLoc;
		sf::Vector2f m_SpawnLoc;

		TimerHandle m_SpawnTimerHandle;

		int m_SpawnAmt;
		int m_CurrentSpawnCount;
	};
}

#endif // TWINBLADESTAGE_H
