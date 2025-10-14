#pragma once
#ifndef HEXAGONSTAGE_H
#define HEXAGONSTAGE_H

#include <SFML/Graphics.hpp>

#include "gameplay/GameStage.h"
#include "framework/TimerManager.h"

namespace ly
{
	class HexagonStage : public GameStage
	{
	public:
		HexagonStage(World* owningWorld) noexcept;

		virtual void StartStage() override;

	private:
		virtual void StageFinished() override;
		void SpawnHexagon();

	private:
		float m_SpawnInterval;
		float m_SideSpawnOffset;

		int m_SpawnGroupAmt;
		int m_CurrentSpawnCount;

		sf::Vector2f m_MidSpawnLoc;
		sf::Vector2f m_LeftSpawnLoc;
		sf::Vector2f m_RightSpawnLoc;

		TimerHandle m_SpawnTimerHandle;
	};
}

#endif //HEXAGONSTAGE_H