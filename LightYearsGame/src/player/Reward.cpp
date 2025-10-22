#include "player/Reward.h"
#include "player/PlayerSpaceship.h"
#include "player/PlayerManager.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/FrontalWiper.h"
#include "framework/World.h"

namespace ly
{
	Reward::Reward(World* owningWorld, const std::string& texturePath, RewardFunc rewardFunc, float speed) noexcept
		: Actor{ owningWorld, texturePath },
		m_Speed{ speed },
		m_RewardFunc{ rewardFunc }
	{

	}

	void Reward::BeginPlay()
	{
		Actor::BeginPlay();

		SetEnablePhysics(true);
	}

	void Reward::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		AddActorLocationOffset({0.0f, m_Speed * deltaTime});
	}

    void Reward::OnActorBeginOverlap(Actor* otherActor)
    {
		// using dynamic_cast here to runtime type check if otherActor is actually the PlayerSpaceship
		// otherwise it will just ignore and return nullptr
		//PlayerSpaceship* playerSpaceship = dynamic_cast<PlayerSpaceship*>(otherActor);
        //if (playerSpaceship != nullptr && !playerSpaceship->IsPendingDestroy())
        //{
        //  m_RewardFunc(playerSpaceship);
		//	Destroy();
        //}

		// Alternative way without dynamic_cast
		if (!otherActor || otherActor->IsPendingDestroy()) return;
		if (!PlayerManager::Get().GetPlayer()) return;

		weak<PlayerSpaceship> playerSpaceship = PlayerManager::Get().GetPlayer()->GetCurrentPlayerSpaceship();
		if (playerSpaceship.expired() || playerSpaceship.lock()->IsPendingDestroy()) return;

		// compare unique IDs to see if they are the same actor
		// instead of comparing pointers directly, which may not be reliable in some cases
		if (playerSpaceship.lock()->GetUniqueID() == otherActor->GetUniqueID())
		{
			m_RewardFunc(playerSpaceship.lock().get());
			Destroy();
		}
	}

	weak<Reward> CreateHealthReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/pill_green.png", RewardHealth);
	}

	weak<Reward> CreateThreeWayShooterReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/three_shooter_pickup.png", RewardThreewayShooter);
	}

	weak<Reward> CreateFrontalWiperReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/front_row_shooter_pickup.png", RewardFrontalWiper);
	}

	weak<Reward> CreateLifeUpReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/playerLife1_blue.png", RewardLifeUp);
	}

	weak<Reward> CreateReward(World* world, const std::string& texturePath, RewardFunc rewardFunc)
	{
		weak<Reward> reward = world->SpawnActor<Reward>(texturePath, rewardFunc);
		return reward;
	}

	void RewardHealth(PlayerSpaceship* player)
	{
		static constexpr float rewardAmt = 10.0f;
		if (player && !player->IsPendingDestroy())
		{
			player->GetHealthComponent().ChangeHealth(rewardAmt);
		}
	}

	void RewardThreewayShooter(PlayerSpaceship* player)
	{
		if (player && !player->IsPendingDestroy())
		{
			player->SetShooter(unique<Shooter>{ new ThreeWayShooter{ player, 0.3f, {50.0f, 0.0f} } });
		}
	}

	void RewardFrontalWiper(PlayerSpaceship* player)
	{
		if (player && !player->IsPendingDestroy())
		{
			player->SetShooter(unique<Shooter>{ new FrontalWiper{ player, 0.6f, {50.0f, 0.0f} } });
		}
	}

	void RewardLifeUp(PlayerSpaceship* player)
	{
		if (!PlayerManager::Get().GetPlayer()) return;

		Player* plyr = PlayerManager::Get().GetPlayer();
		if (plyr)
		{
			plyr->AddLifeCount(1);
		}
	}
}
