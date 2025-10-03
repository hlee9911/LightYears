#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>

#include "framework/Core.h"
#include "framework/Object.h"

namespace ly
{
	class Actor; // forward declaration
	class Application; // forward declaration

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

	private:
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);

	private:
		Application* m_OwningApp;
		bool m_HasBegunPlay;

		List<shared<Actor>> m_Actors; // all actors in the world
		List<shared<Actor>> m_PendingActors; // actors to be added next frame
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
