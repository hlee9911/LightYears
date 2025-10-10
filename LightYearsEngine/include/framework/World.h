#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>

#include "framework/Core.h"
#include "framework/Object.h"

namespace ly
{
	class Actor;
	class Application;
	class GameStage;

	class World : public Object
	{
	public:
		World(Application* owningApp) noexcept;

		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		void Render(sf::RenderWindow& window);

		virtual ~World() noexcept;

		template<typename ActorType, typename... Args>
		weak<ActorType> SpawnActor(Args... args);

		sf::Vector2u GetWorldSize() const noexcept;
		void CleanCycle();
		void AddStage(const shared<GameStage>& newStage);

	private:
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);

		virtual void InitGameStages();
		void NextGameStage();
		virtual void AllGameStageFinished();

	private:
		Application* m_OwningApp;
		bool m_HasBegunPlay;

		List<shared<Actor>> m_Actors; // all actors in the world
		List<shared<Actor>> m_PendingActors; // actors to be added next frame

		// using shared pointer becuase the timer has to work with the weak references
		// and only shared pointer has that
		List<shared<GameStage>> m_GameStages; // list of game stages
		int m_CurrentStageIndex;
 	};

	template<typename ActorType, typename... Args>
	weak<ActorType> World::SpawnActor(Args... args)
	{
		shared<ActorType> newActor{ new ActorType(this, args...) };
		m_PendingActors.push_back(newActor);
		return newActor;
	}
}

#endif // WORLD_H
