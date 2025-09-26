#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/PhysicsSystem.h"

namespace ly
{
	Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style) noexcept
		: m_Window{ sf::VideoMode(windowWidth, windowHeight), title, style },
		m_TargetFrameRate{ 60.0f },
		m_TickClock{},
		m_CurrentWorld{ nullptr },
		m_CleanCycleClock{},
		m_CleanCycleInterval{ 2.0f } // clean every 2 seconds
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
			m_CurrentWorld->TickInternal(deltaTime);
		}

		// Physics Calculation
		PhysicsSystem::Get().Step(deltaTime);

		// perform asset manager clean cycle every interval seconds
		if (m_CleanCycleClock.getElapsedTime().asSeconds() >= m_CleanCycleInterval)
		{
			m_CleanCycleClock.restart();
			AssetManager::Get().CleanCycle();
			// make sure the world also cleans up its actors
			// periodically to avoid accessing the memory frequently
			if (m_CurrentWorld)
			{
				m_CurrentWorld->CleanCycle();
			}
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
		//// to be overridden by derived classes

		//// draw a green rectangle in the center of the window
		//sf::CircleShape rect{ 50 };
		//rect.setFillColor(sf::Color::Green);
		//rect.setOrigin(50, 50);
		//rect.setPosition(m_Window.getSize().x / 2.0f, m_Window.getSize().y / 2.0f);

		//m_Window.draw(rect);
		if (m_CurrentWorld)
		{
			m_CurrentWorld->Render(m_Window);
		}
	}

	void Application::Tick(float deltaTime)
	{

	}
}
