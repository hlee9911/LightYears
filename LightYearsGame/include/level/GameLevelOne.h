#pragma once
#ifndef GAMELEVELONE_H
#define GAMELEVELONE_H

#include "framework/World.h"
#include "framework/TimerManager.h"

namespace ly
{
	class PlayerSpaceship;
	class GameLevelOne : public World
	{
	public:
		GameLevelOne(Application* owningApp) noexcept;
	
	private:
		virtual void BeginPlay() override;
		// void TimerCallBack_Test(); // for debugging purpose
		virtual void InitGameStages() override;
		void PlayerSpaceshipDestroyed(Actor* destroyedPlayerSpaceship);
		void GameOver();

	private:
		weak<PlayerSpaceship> m_PlayerSpaceship;
		TimerHandle m_TimerHandle_Test;
	};
}

#endif // GAMELEVELONE_H
