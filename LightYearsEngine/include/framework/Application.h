#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Graphics.hpp>

namespace ly // Lightyear
{
	class Application
	{
	public:
		Application() noexcept;
		void Run() noexcept;

	private:
		void TickInternal(float deltaTime);
		void RenderInternal() noexcept;
		
		virtual void Render();
		virtual void Tick(float deltaTime);

		sf::RenderWindow m_Window;
		float m_TargetFrameRate;
		sf::Clock m_TickClock;
	};
}

#endif // Application.h
