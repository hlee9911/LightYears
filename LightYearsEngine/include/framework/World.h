#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>

#include "framework/Core.h"

namespace ly
{
	class Actor; // forward declaration
	class Application; // forward declaration

	class World 
	{
	public:
		World(Application* owningApp) noexcept;

		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		void Render(sf::RenderWindow& window);

		virtual ~World() noexcept;

		template<typename ActorType>
		weak<ActorType> SpawnActor();

		sf::Vector2u GetWorldSize() const noexcept;

	private:
		void BeginPlay();
		void Tick(float deltaTime);

	private:
		Application* m_OwningApp;
		bool m_HasBegunPlay;

		List<shared<Actor>> m_Actors; // all actors in the world
		List<shared<Actor>> m_PendingActors; // actors to be added next frame
 	};

	template<typename ActorType>
	weak<ActorType> World::SpawnActor()
	{
		shared<ActorType> newActor{ new ActorType{this} };
		m_PendingActors.push_back(newActor);
		return newActor;
	}
}

#endif // WORLD_H
