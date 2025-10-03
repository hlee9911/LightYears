#pragma once
#ifndef GAMELEVELONE_H
#define GAMELEVELONE_H

#include "framework/World.h"

namespace ly
{
	class PlayerSpaceship;
	class GameLevelOne : public World
	{
	public:
		GameLevelOne(Application* owningApp) noexcept;
	
	private:
		virtual void BeginPlay() override;

	private:
		weak<PlayerSpaceship> m_TestPlayerSpaceship;
		void TimerCallBack_Test();
	};
}

#endif // GAMELEVELONE_H
