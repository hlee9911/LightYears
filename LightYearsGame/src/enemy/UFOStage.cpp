#include "enemy/UFOStage.h"
#include "enemy/UFO.h"
#include "framework/World.h"
#include "framework/MathUtility.h"
#include "weapon/BulletShooter.h"

namespace ly
{
	UFOStage::UFOStage(World* owningWorld) noexcept
		: GameStage{ owningWorld },
		m_SpawnInterval{ 4.0f },
		m_SpawnAmt{ 10 },
		m_CurrentSpawnAmt{ 0 },
		m_UFOSpeed{ 250.0f }
	{

	}

	void UFOStage::StartStage()
	{
		m_SpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &UFOStage::SpawnUFO, m_SpawnInterval, true);
	}

	void UFOStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(m_SpawnTimerHandle);
		LOG("UFOStage Stage Finished");
	}

	sf::Vector2f UFOStage::GetRandomSpawnLoc() const
	{
		auto windowSize = GetWorld()->GetWorldSize();

		float spawnLeft = RandomRange(-1.0f, 1.0f);
		float spawnLocX = 0.0f;
		if (spawnLeft < 0.0f)
		{
			spawnLocX = windowSize.x + 100.0f;
		}
		else
		{
			spawnLocX = -100.0f;
		}

		float spawnLocY = RandomRange(0.0f, windowSize.y);
		return sf::Vector2f{ spawnLocX, spawnLocY };
	}

	/// <summary>
	/// Spawns UFOs and set their spawn location at random and have them move towards center of the screen
	/// </summary>
	void UFOStage::SpawnUFO()
	{
		sf::Vector2f spawnLoc = GetRandomSpawnLoc();
		auto windowSize = GetWorld()->GetWorldSize();
		sf::Vector2f center{ windowSize.x / 2.0f, windowSize.y / 2.0f };
		sf::Vector2f spawnLocToCenter{ center.x - spawnLoc.x, center.y - spawnLoc.y };
		NormalizeVector(spawnLocToCenter);

		sf::Vector2f spawnVelocity = spawnLocToCenter * m_UFOSpeed;

		weak<UFO> newUFO = GetWorld()->SpawnActor<UFO>(spawnVelocity);
		newUFO.lock()->SetActorLocation(spawnLoc);

		if (++m_CurrentSpawnAmt >= m_SpawnAmt)
		{
			FinishStage();
		}
	}
}
