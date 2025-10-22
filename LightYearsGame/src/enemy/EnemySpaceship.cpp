#include "enemy/EnemySpaceship.h"
#include "framework/MathUtility.h"
#include "player/PlayerManager.h"

namespace ly
{
	EnemySpaceship::EnemySpaceship(World* owningWorld, const std::string& texturePath, float collisionDamage, float rewardDropWeight, const List<RewardFactoryFunc> rewards) noexcept
		: Spaceship{ owningWorld, texturePath },
		m_CollisionDamage{ collisionDamage },
		m_RewardFactories{ rewards },
		m_ScoreAwardAmt{ 100 },
		m_RewardDropWeight{ rewardDropWeight }
	{
		SetTeamID(2); // Enemy team ID is 2
	}

	void EnemySpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);

		if (IsActorOutOfWindowsBounds(GetActorGlobalBounds().width * 2.0f))
		{
			Destroy();
		}
	}

	void EnemySpaceship::SpawnReward()
	{
		if (m_RewardFactories.size() == 0) return;

		// constexpr float dropRate = 0.50f; // drop rate
		bool isSpawningReward = RandomRange(0.0f, 1.0f) <= m_RewardDropWeight;

		// choose pickups randomly and spawn them at the current actor location
		int pick = (int)RandomRange(0, m_RewardFactories.size());
		if (isSpawningReward && (pick >= 0 && pick < m_RewardFactories.size()))
		{
			weak<Reward> newReward = m_RewardFactories[pick](GetWorld());
			newReward.lock()->SetActorLocation(GetActorLocation());
		}
	}

	void EnemySpaceship::OnActorBeginOverlap(Actor* otherActor)
	{
		Spaceship::OnActorBeginOverlap(otherActor);

		if (IsOtherHostile(otherActor))
		{
			otherActor->ApplyDamage(m_CollisionDamage);
		}
	}

	void EnemySpaceship::Blew()
	{
		SpawnReward();
		Player* player = PlayerManager::Get().GetPlayer();
		if (player)
		{
			player->AddScore(m_ScoreAwardAmt);
		}
	}
}
