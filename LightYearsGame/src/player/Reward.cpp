#include "player/Reward.h"
#include "player/PlayerSpaceship.h"

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
        // TODO: clean up casting
		PlayerSpaceship* playerSpaceship = static_cast<PlayerSpaceship*>(otherActor);
        if (playerSpaceship != nullptr && !playerSpaceship->IsPendingDestroy())
        {
            m_RewardFunc(playerSpaceship);
        }
    }
}
