#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "framework/Object.h"
#include "framework/Delegate.h"

namespace ly
{
	class PlayerSpaceship;
	class World;
	class Player : public Object
	{
	public:
		Player() noexcept;

		weak<PlayerSpaceship> SpawnSpaceship(World* world);
		const weak<PlayerSpaceship> GetCurrentPlayerSpaceship() const noexcept { return m_CurrentPlayerSpaceship; }

		void AddLifeCount(unsigned int amt);
		int GetPlayerLifeCount() const noexcept { return m_PlayerLifeCount; }
		
		void AddScore(unsigned int amt);
		int GetScore() const noexcept { return m_Score; }

		Delegate<int> onLifeCountChanged;
		Delegate<int> onScoreChanged;
		Delegate<> onLifeExhausted;

	private:
		unsigned int m_PlayerLifeCount;
		unsigned int m_Score;
		weak<PlayerSpaceship> m_CurrentPlayerSpaceship;
	};
}

#endif // PLAYER_H
