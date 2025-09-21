#pragma once
#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics.hpp>
#include <string>

#include "framework/Core.h"
#include "framework/Object.h"

namespace ly
{
	class World; // Forward declaration of World class

	class Actor : public Object
	{
	public:
		Actor(World* owningWorld, const std::string& texturePath = "") noexcept;
		virtual ~Actor() noexcept;

		void BeginPlayInternal();
		void TickInternal(float deltaTime);

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);

		void SetTexture(const std::string& texturePath);
		void Render(sf::RenderWindow& window);

	private:
		World* m_OwningWorld;
		bool m_HasBegunPlay;
	
		sf::Sprite m_Sprite;
		shared<sf::Texture> m_Texture;
	};
}

#endif // ACTOR_H
