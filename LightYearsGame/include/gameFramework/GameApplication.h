#pragma once
#ifndef GAMEAPPLICATION_H
#define GAMEAPPLICATION_H

#include <framework/Application.h>
#include <framework/Core.h>

namespace ly
{
	class Actor;
	class GameApplication : public Application
	{
	public:
		GameApplication() noexcept;

		virtual void Tick(float deltaTime) override;
	
	private:
		float m_Counter;
		weak<Actor> m_ActorToDestroy;
	};
}

#endif // GAMEAPPLICATION_H