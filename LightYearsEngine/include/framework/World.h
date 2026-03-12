#pragma once

#include <SFML/Graphics.hpp>

#include "framework/Core.h"
#include "framework/Object.h"

namespace ly
{
	class Actor;
	class HUD;
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

		template<typename HUDType, typename... Args>
		weak<HUDType> SpawnHUD(Args... args);

		sf::Vector2u GetWorldSize() const noexcept;
		void CleanCycle();
		void AddStage(const shared<GameStage>& newStage);
		bool DispatchEvent(const sf::Event& event);
		Application* GetOwningApplication() noexcept { return m_OwningApp; }
		const Application* GetOwningApplication() const noexcept { return m_OwningApp; }

	private:
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		void RenderHUD(sf::RenderWindow& window);

		virtual void InitGameStages();
		void NextGameStage();
		void StartStages();

		virtual void AllGameStagesFinished();

	private:
		Application* m_OwningApp;
		bool m_HasBegunPlay;

		List<shared<Actor>> m_Actors; // all actors in the world
		List<shared<Actor>> m_PendingActors; // actors to be added next frame

		// using shared pointer becuase the timer has to work with the weak references
		// and only shared pointer has that
		List<shared<GameStage>> m_GameStages; // list of game stages
		// int m_CurrentStageIndex;

		List<shared<GameStage>>::iterator m_CurrentStage;

		shared<HUD> m_HUD;
 	};

	template<typename ActorType, typename... Args>
	weak<ActorType> World::SpawnActor(Args... args)
	{
		shared<ActorType> newActor{ new ActorType(this, args...) };
		m_PendingActors.push_back(newActor);
		return newActor;
	}

	template<typename HUDType, typename... Args>
	inline weak<HUDType> World::SpawnHUD(Args... args)
	{
		shared<HUDType> newHUD{ new HUDType(args...) };
		m_HUD = newHUD;
		return newHUD;
	}
}
