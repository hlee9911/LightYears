#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "framework/Core.h"

namespace ly // Lightyear
{
	class World; // forward declaration, this has the ownership of the world

	class Application
	{
	public:
		Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style) noexcept;
		void Run() noexcept;

		template <typename WorldType>
		weak<WorldType> LoadWorld(); // shouldnt supposed to have the ownership of the world

		sf::Vector2u GetWindowSize() const noexcept { return m_Window.getSize(); }
		sf::RenderWindow& GetWindow() noexcept { return m_Window; }
		const sf::RenderWindow& GetWindow() const noexcept { return m_Window; }

		void QuitApplication() noexcept;

	private:
		// internal functions
		bool DispatchEvent(const sf::Event& event);

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
		shared<World> m_PendingWorld;

		sf::Clock m_CleanCycleClock;
		float m_CleanCycleInterval; // in seconds
	};

	template <typename WorldType>
	weak<WorldType> Application::LoadWorld()
	{
		shared<WorldType> newWorld{ new WorldType{this} };
		m_PendingWorld = newWorld;
		// dont call BeginPlayInternal() right away, wait for a bit
		// m_PendingWorld->BeginPlayInternal();
		return newWorld;
	}
}
