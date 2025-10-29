#include "enemy/HexagonStage.h"
#include "enemy/Hexagon.h"
#include "framework/World.h"
#include "weapon/BulletShooter.h"

namespace ly
{
	HexagonStage::HexagonStage(World* owningWorld) noexcept
		: GameStage{ owningWorld },
		m_SpawnInterval{ 5.0f },
		m_SideSpawnOffset{ 80.0f },
		m_SpawnGroupAmt{ 5 },
		m_CurrentSpawnCount{ 0 },
		m_MidSpawnLoc{ owningWorld->GetWorldSize().x / 2.0f, -100.0f },
		m_RightSpawnLoc{ owningWorld->GetWorldSize().x / 2.0f + m_SideSpawnOffset, -100.0f - m_SideSpawnOffset },
		m_LeftSpawnLoc{ owningWorld->GetWorldSize().x / 2.0f - m_SideSpawnOffset, -100.0f - m_SideSpawnOffset }
	{

	}

	void HexagonStage::StartStage()
	{
		m_SpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &HexagonStage::SpawnHexagon, m_SpawnInterval, true);
	}

	void HexagonStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(m_SpawnTimerHandle);
		LOG("HexagonStage Stage Finished");
	}

	void HexagonStage::SpawnHexagon()
	{
		weak<Hexagon> newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetActorLocation(m_MidSpawnLoc);

		newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetActorLocation(m_LeftSpawnLoc);

		newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetActorLocation(m_RightSpawnLoc);

		if (++m_CurrentSpawnCount == m_SpawnGroupAmt)
		{
			FinishStage();
		}
	}
}
