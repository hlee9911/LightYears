#pragma once
#ifndef GAMEAPPLICATION_H
#define GAMEAPPLICATION_H

#include <framework/Application.h>
#include <framework/Core.h>

namespace ly
{
	class Actor;
	class PlayerSpaceship;
	class GameApplication : public Application
	{
	public:
		GameApplication() noexcept;

		virtual void Tick(float deltaTime) override;
	
	private:
		float m_Counter;
		weak<PlayerSpaceship> m_TestPlayerSpaceship;
	};
}

#endif // GAMEAPPLICATION_H