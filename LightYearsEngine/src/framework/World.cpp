#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include "gameplay/GameStage.h"

namespace ly
{
	World::World(Application* owningApp) noexcept
		: m_OwningApp{ owningApp },
		m_HasBegunPlay{ false },
		m_Actors{},
		m_PendingActors{},
		m_GameStages{},
		m_CurrentStage{ m_GameStages.end() }
	{

	}

	void World::BeginPlayInternal()
	{
		if (!m_HasBegunPlay)
		{
			m_HasBegunPlay = true;
			BeginPlay();
			InitGameStages();
			// NextGameStage();
			StartStages();
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

		for (auto iter = m_Actors.begin(); iter != m_Actors.end();)
		{
			iter->get()->TickInternal(deltaTime);
			++iter;
		}

		if (m_CurrentStage != m_GameStages.end())
		{
			m_CurrentStage->get()->TickStage(deltaTime);
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

	// clean up actors and stages that are pending destroy
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

		//// cleaning game stages part
		//for (auto iter = m_GameStages.begin(); iter != m_GameStages.end();)
		//{
		//	if (iter->get()->IsStageFinished())
		//	{
		//		iter = m_GameStages.erase(iter);
		//	}
		//	else
		//	{
		//		++iter;
		//	}
		//}
	}

	void World::AddStage(const shared<GameStage>& newStage)
	{
		m_GameStages.push_back(newStage);
	}

	void World::BeginPlay()
	{
		// LOG("Begun play");
	}

	void World::Tick(float deltaTime)
	{
		// LOG("Ticking at frame rate: %f", 1.0f / deltaTime);
	}

	void World::InitGameStages()
	{

	}

	void World::NextGameStage()
	{
		m_CurrentStage = m_GameStages.erase(m_CurrentStage);
		if (m_CurrentStage != m_GameStages.end())
		{
			m_CurrentStage->get()->StartStage();
			// bind the action to move onto the next stage when we invoke current stage event finished event
			m_CurrentStage->get()->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
		}
		else
		{
			AllGameStageFinished();
		}
	}

	void World::StartStages()
	{
		m_CurrentStage = m_GameStages.begin();
		m_CurrentStage->get()->StartStage();
		// bind the action to move onto the next stage when we invoke current stage event finished event
		m_CurrentStage->get()->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
	}

	void World::AllGameStageFinished()
	{
		LOG("All Stages Finished");
	}

}
