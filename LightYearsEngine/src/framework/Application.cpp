#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"

namespace ly
{
	Application::Application() noexcept
		: m_Window{ sf::VideoMode(1024, 1440), "Light Years" },
		m_TargetFrameRate{ 60.0f },
		m_TickClock{},
		m_CurrentWorld{ nullptr }
	{

	}

	void Application::Run() noexcept
	{
		m_TickClock.restart(); // restart the clock to avoid a large delta time on the first frame
		float accumulatedTime = 0.0f;
		float targetDeltaTime = 1.0f / m_TargetFrameRate;
		while (m_Window.isOpen())
		{
			sf::Event windowEvent;
			while (m_Window.pollEvent(windowEvent))
			{
				// handle window close event
				if (windowEvent.type == sf::Event::EventType::Closed) m_Window.close();

				// handle when escape key is pressed, close the window
				if (windowEvent.type == sf::Event::EventType::KeyPressed)
				{
					if (windowEvent.key.code == sf::Keyboard::Escape) m_Window.close();
				}
			}


			float frameDeltaTime = m_TickClock.restart().asSeconds();
			// fixed timestep update
			accumulatedTime += frameDeltaTime;
			// update while we have enough accumulated time
			while (accumulatedTime >= targetDeltaTime)
			{
				// update
				accumulatedTime -= targetDeltaTime;
				TickInternal(targetDeltaTime);
				RenderInternal();
			}

			// for debugging, print out the current framerate (acutal framerate)
			// LOG("Ticking at framerate: %.2f FPS", 1.0f / frameDeltaTime);
		}
	}

	void Application::TickInternal(float deltaTime)
	{
		// call the application tick
		Tick(deltaTime);

		if (m_CurrentWorld)
		{
			// m_CurrentWorld->BeginPlayInternal();
			m_CurrentWorld->TickInternal(deltaTime);
		}
	}

	void Application::RenderInternal() noexcept
	{
		m_Window.clear();

		Render();

		m_Window.display();
	}

	void Application::Render()
	{
		// to be overridden by derived classes
		
		// draw a green rectangle in the center of the window
		sf::CircleShape rect{ 50 };
		rect.setFillColor(sf::Color::Green);
		rect.setOrigin(50, 50);
		rect.setPosition(m_Window.getSize().x / 2.0f, m_Window.getSize().y / 2.0f);

		m_Window.draw(rect);
	}

	void Application::Tick(float deltaTime)
	{

	}
}
