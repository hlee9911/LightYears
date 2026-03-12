#pragma once

#include <SFML/Graphics.hpp>

#include "gameplay/GameStage.h"
#include "framework/TimerManager.h"

namespace ly
{
	class VanguardStage : public GameStage
	{
	public:
		VanguardStage(World* owningWorld) noexcept;

		virtual void StartStage() override;

	private:
		virtual void StageFinished() override;
		void SpawnVanguard();
		void SwitchRow();

	private:
		float m_SpawnInterval;
		float m_SwitchInterval; // waiting time between each row
		float m_SpawnDistanceToEdge;

		sf::Vector2f m_LeftSpawnLoc;
		sf::Vector2f m_RightSpawnLoc;
		sf::Vector2f m_SpawnLoc;

		TimerHandle m_SpawnTimerHandle;
		TimerHandle m_SwitchTimerHandle;

		int m_RowsToSpawn;
		int m_RowSpawnCount;

		int m_VanguardPerRow;
		int m_CurrentRowVanguardCount;
	};
}
