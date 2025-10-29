#include "player/Player.h"
#include "player/PlayerSpaceship.h"
#include "framework/World.h"
#include "weapon/BulletShooter.h"

namespace ly
{
	Player::Player() noexcept
		: m_PlayerLifeCount{ 3 },
		m_Score{ 0 },
		m_CurrentPlayerSpaceship{}
	{

	}

	weak<PlayerSpaceship> Player::SpawnSpaceship(World* world)
	{
		if (m_PlayerLifeCount > 0)
		{
			--m_PlayerLifeCount;
			auto windowSize = world->GetWorldSize();
			m_CurrentPlayerSpaceship = world->SpawnActor<PlayerSpaceship>();
			m_CurrentPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f{ windowSize.x / 2.0f, windowSize.y - 100.0f });
			// m_CurrentPlayerSpaceship.lock()->SetActorRotation(-90.0f);
			onLifeCountChanged.Broadcast(m_PlayerLifeCount);
			return m_CurrentPlayerSpaceship;
		}
		else
		{
			m_CurrentPlayerSpaceship = weak<PlayerSpaceship>{}; // make sure to clear the current spaceship reference
			onLifeExhausted.Broadcast();
		}
		return weak<PlayerSpaceship>{};
	}

	void Player::AddLifeCount(unsigned int amt)
	{
		if (amt > 0)
		{
			m_PlayerLifeCount += amt;
			onLifeCountChanged.Broadcast(m_PlayerLifeCount);
		}
	}

	void Player::AddScore(unsigned int amt)
	{
		if (amt > 0)
		{
			m_Score += amt;
			onScoreChanged.Broadcast(m_Score);
		}
	}
}
