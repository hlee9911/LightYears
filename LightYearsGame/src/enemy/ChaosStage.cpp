#include "enemy/ChaosStage.h"
#include "enemy/Vanguard.h"
#include "enemy/TwinBlade.h"
#include "enemy/Hexagon.h"
#include "enemy/UFO.h"
#include "framework/World.h"
#include "framework/MathUtility.h"
#include "weapon/BulletShooter.h"

namespace ly
{
	ChaosStage::ChaosStage(World* owningWorld) noexcept
		: GameStage{ owningWorld },
		m_SpawnInterval{ 4.0f },
		m_MinSpawnInterval{ 0.8f },
		m_SpawnIntervalDecrement{ 0.5f },
		m_SpawnIntervalDecrementInterval{ 5.0f },
		m_StageDuration{ 60.0f }
	{

	}

	void ChaosStage::StartStage()
	{
		m_SpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnVanguard, m_SpawnInterval);
		m_DifficultTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::IncreaseDifficulty, m_SpawnIntervalDecrementInterval, true);
		TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::StageDurationReached, m_StageDuration);
	}

	void ChaosStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(m_SpawnTimerHandle);
		TimerManager::Get().ClearTimer(m_DifficultTimerHandle);
	}

	void ChaosStage::SpawnVanguard()
	{
		weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>();
		newVanguard.lock()->SetActorLocation(GetRandomSpawnLocationTop());
		m_SpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnTwinBlade, m_SpawnInterval);
	}

	void ChaosStage::SpawnTwinBlade()
	{
		weak<TwinBlade> newTwinBlade = GetWorld()->SpawnActor<TwinBlade>();
		newTwinBlade.lock()->SetActorLocation(GetRandomSpawnLocationTop());
		m_SpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnHexagon, m_SpawnInterval);
	}

	void ChaosStage::SpawnHexagon()
	{
		weak<Hexagon> newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetActorLocation(GetRandomSpawnLocationTop());
		m_SpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnUFO, m_SpawnInterval);
	}

	void ChaosStage::SpawnUFO()
	{
		sf::Vector2f spawnLoc = GetRandomSpawnLocationSide();

		auto windowSize = GetWorld()->GetWorldSize();
		sf::Vector2f center = sf::Vector2f{ windowSize.x / 2.0f, windowSize.y / 2.0f };
		sf::Vector2f dirToCenter = center - spawnLoc;
		NormalizeVector(dirToCenter);

		weak<UFO> newUFO = GetWorld()->SpawnActor<UFO>(dirToCenter * 200.0f);
		newUFO.lock()->SetActorLocation(spawnLoc);

		m_SpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnVanguard, m_SpawnInterval);
	}

	/// <summary>
	/// This function increases the difficulty of the stage by reducing the spawn interval.
	/// </summary>
	void ChaosStage::IncreaseDifficulty()
	{
		m_SpawnInterval -= m_SpawnIntervalDecrement;
		if (m_SpawnInterval < m_MinSpawnInterval)
		{
			m_SpawnInterval = m_MinSpawnInterval;
		}
	}

	void ChaosStage::StageDurationReached()
	{
		FinishStage();
	}

	sf::Vector2f ChaosStage::GetRandomSpawnLocationTop() const
	{
		auto windowSize = GetWorld()->GetWorldSize();
		float spawnX = RandomRange(100.0f, windowSize.x - 100.0f);
		float spawnY = -100.0f;
		return sf::Vector2f{ spawnX, spawnY };
	}

	sf::Vector2f ChaosStage::GetRandomSpawnLocationSide() const
	{
		auto windowSize = GetWorld()->GetWorldSize();
		float spawnLeft = RandomRange(-1.0f, 1.0f);
		float spawnLocX = 0.0f;
		spawnLocX = (spawnLeft < 0.0f) ? windowSize.x + 100.0f : -100.0f;

		float spawnLocY = RandomRange(0.0f, windowSize.y);
		return sf::Vector2f{ spawnLocX, spawnLocY };
	}
}
