#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Graphics.hpp>

#include "framework/Core.h"

namespace ly // Lightyear
{
	class World; // forward declaration, this has the ownership of the world

	class Application
	{
	public:
		Application() noexcept;
		void Run() noexcept;

		template <typename WorldType>
		weak<World> LoadWorld(); // shouldnt supposed to have the ownership of the world

	private:
		void TickInternal(float deltaTime);
		void RenderInternal() noexcept;
		
		virtual void Render();
		virtual void Tick(float deltaTime);

	private:
		// members variables
		sf::RenderWindow m_Window;
		float m_TargetFrameRate;
		sf::Clock m_TickClock;

		shared<World> m_CurrentWorld;
	};

	template <typename WorldType>
	weak<World> Application::LoadWorld()
	{
		shared<WorldType> newWorld{ new WorldType{this} };
		m_CurrentWorld = newWorld;
		m_CurrentWorld->BeginPlayInternal();
		return newWorld;
	}
}

#endif // Application.h
