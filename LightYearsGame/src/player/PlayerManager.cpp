#include "player/PlayerManager.h"

namespace ly
{
	unique<PlayerManager> PlayerManager::s_PlayerManager{ nullptr };

	PlayerManager::PlayerManager() noexcept
		: m_Players{}
	{

	}

	Player& PlayerManager::CreateNewPlayer()
	{
		m_Players.emplace(m_Players.begin(), Player());
		return m_Players.back();
	}

	Player* PlayerManager::GetPlayer(int playerIndex)
	{
		if (playerIndex >= 0 && playerIndex <= m_Players.size())
		{
			return &(m_Players[playerIndex]);
		}
		return nullptr;
	}

	const Player* PlayerManager::GetPlayer(int playerIndex) const
	{
		if (playerIndex >= 0 && playerIndex <= m_Players.size())
		{
			return &(m_Players[playerIndex]);
		}
		return nullptr;
	}

	PlayerManager& PlayerManager::Get()
	{
		if (!s_PlayerManager)
		{
			s_PlayerManager = std::move(unique<PlayerManager>{ new PlayerManager{} });
		}
		return *s_PlayerManager;
	}

	void PlayerManager::Reset()
	{
		m_Players.clear();
	}
}
