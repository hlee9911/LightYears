#include "enemy/VanguardStage.h"
#include "enemy/Vanguard.h"
#include "framework/World.h"

namespace ly
{
	VanguardStage::VanguardStage(World* owningWorld) noexcept
		: GameStage{ owningWorld },
		m_SpawnInterval{ 1.5f },
		m_SwitchInterval{ 3.0f },
		m_SpawnDistanceToEdge{ 100.0f },
		m_LeftSpawnLoc{ 0.0f, 0.0f },
		m_RightSpawnLoc{ 0.0f, 0.0f },
		m_SpawnLoc{ 0.0f, 0.0f },
		m_RowsToSpawn{ 2 },
		m_RowSpawnCount{ 0 },
		m_VanguardPerRow{ 5 },
		m_CurrentRowVanguardCount{ 0 }
	{

	}

	void VanguardStage::StartStage()
	{
		auto windowSize = GetWorld()->GetWorldSize();
		m_LeftSpawnLoc = sf::Vector2f{ m_SpawnDistanceToEdge, -100.0f }; // this much from the left edge and from the top edge
		m_RightSpawnLoc = sf::Vector2f{ windowSize.x - m_SpawnDistanceToEdge, -100.0f };

		SwitchRow();
	}

	void VanguardStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(m_SpawnTimerHandle);
		TimerManager::Get().ClearTimer(m_SwitchTimerHandle);
		LOG("Vanguard Stage Finished");
	}

	void VanguardStage::SpawnVanguard()
	{
		weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>();
		newVanguard.lock()->SetActorLocation(m_SpawnLoc);
		++m_CurrentRowVanguardCount;

		if (m_CurrentRowVanguardCount == m_VanguardPerRow)
		{
			TimerManager::Get().ClearTimer(m_SpawnTimerHandle);
			m_SwitchTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SwitchRow, m_SwitchInterval, false);
			m_CurrentRowVanguardCount = 0;
		}
	}

	void VanguardStage::SwitchRow()
	{
		if (m_RowSpawnCount == m_RowsToSpawn)
		{
			FinishStage();
			return; // we are at the end of the row, just return and finish the stage
		}

		// if we are currently on the left land that we are spawning,
		if (m_SpawnLoc == m_LeftSpawnLoc)
		{
			m_SpawnLoc = m_RightSpawnLoc; // we make it right spawn location
		}
		else
		{
			m_SpawnLoc = m_LeftSpawnLoc;
		}

		m_SpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SpawnVanguard, m_SpawnInterval, true);
	
		++m_RowSpawnCount;
	}

}
