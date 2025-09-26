#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"

namespace ly
{
	World::World(Application* owningApp) noexcept
		: m_OwningApp{ owningApp },
		m_HasBegunPlay{ false },
		m_Actors{},
		m_PendingActors{}
	{

	}

	void World::BeginPlayInternal()
	{
		if (!m_HasBegunPlay)
		{
			m_HasBegunPlay = true;
			BeginPlay();
		}
	}

	void World::TickInternal(float deltaTime)
	{
		for (auto actor : m_PendingActors)
		{
			m_Actors.push_back(actor);
			actor->BeginPlayInternal();
		}
		m_PendingActors.clear();

		//for (auto& actor : m_Actors)
		//{
		//	actor->Tick(deltaTime);
		//}

		// memory management part:
		// doing instant deletion of actors while iterating through the list.
		// good for small game, but for larger game, we might want to implement 
		// a more sophisticated memory management system
		for (auto iter = m_Actors.begin(); iter != m_Actors.end();)
		{
			iter->get()->TickInternal(deltaTime);
			++iter;
		}

		Tick(deltaTime);
	}

	void World::Render(sf::RenderWindow& window)
	{
		for (auto& actor : m_Actors)
		{
			actor->Render(window);
		}
	}

	World::~World() noexcept
	{

	}

	sf::Vector2u World::GetWorldSize() const noexcept
	{
		return m_OwningApp->GetWindowSize();
	}

	// clean up actors that are pending destroy
	void World::CleanCycle()
	{
		// memory management part:
		// doing instant deletion of actors while iterating through the list.
		// good for small game, but for larger game, we might want to implement 
		// a more sophisticated memory management system
		for (auto iter = m_Actors.begin(); iter != m_Actors.end();)
		{
			if (iter->get()->IsPendingDestroy())
			{
				// removes the actor from the world's actor list
				iter = m_Actors.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}

	void World::BeginPlay()
	{
		// LOG("Begun play");
	}

	void World::Tick(float deltaTime)
	{
		// LOG("Ticking at frame rate: %f", 1.0f / deltaTime);
	}
}
