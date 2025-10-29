#include "enemy/TwinBladeStage.h"
#include "enemy/TwinBlade.h"
#include "framework/World.h"
#include "weapon/BulletShooter.h"

namespace ly
{
	TwinBladeStage::TwinBladeStage(World* owningWorld) noexcept
		: GameStage{ owningWorld },
		m_SpawnInterval{ 1.5f },
		m_SpawnDistanceToCenter{ 100.0f },
		m_LeftSpawnLoc{ owningWorld->GetWorldSize().x / 2.0f - m_SpawnDistanceToCenter, -100.0f },
		m_RightSpawnLoc{ owningWorld->GetWorldSize().x / 2.0f + m_SpawnDistanceToCenter, -100.0f },
		m_SpawnLoc{ m_LeftSpawnLoc },
		m_SpawnAmt{ 10 },
		m_CurrentSpawnCount{ 0 }
	{

	}

	void TwinBladeStage::StartStage()
	{
		m_SpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &TwinBladeStage::SpawnTwinBlade, m_SpawnInterval, true);
	}

	void TwinBladeStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(m_SpawnTimerHandle);
		LOG("TwinBlade Stage Finished");
	}

	void TwinBladeStage::SpawnTwinBlade()
	{
		weak<TwinBlade> newTwinBlade = GetWorld()->SpawnActor<TwinBlade>();
		newTwinBlade.lock()->SetActorLocation(m_SpawnLoc);
		if (m_SpawnLoc == m_LeftSpawnLoc)
		{
			m_SpawnLoc = m_RightSpawnLoc;
		}
		else
		{
			m_SpawnLoc = m_LeftSpawnLoc;
		}

		++m_CurrentSpawnCount;
		if (m_CurrentSpawnCount >= m_SpawnAmt)
		{
			FinishStage();
		}
	}
}
