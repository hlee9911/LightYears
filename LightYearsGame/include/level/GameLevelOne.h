#pragma once

#include "framework/World.h"
#include "framework/TimerManager.h"

namespace ly
{
	class PlayerSpaceship;
	class GameplayHUD;
	class GameLevelOne : public World
	{
	public:
		GameLevelOne(Application* owningApp) noexcept;
	
	private:
		virtual void AllGameStagesFinished() override;
		virtual void BeginPlay() override;
		// void TimerCallBack_Test(); // for debugging purpose
		virtual void InitGameStages() override;
		void PlayerSpaceshipDestroyed(Actor* destroyedPlayerSpaceship);
		
		void QuitGame();
		void RestartGame();
		
		void GameOver();

		void SpawnCosmetics();

	private:
		weak<PlayerSpaceship> m_PlayerSpaceship;
		weak<GameplayHUD> m_GameplayHUD;
		TimerHandle m_TimerHandle_Test;
	};
}
