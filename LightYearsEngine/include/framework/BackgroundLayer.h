#pragma once
#ifndef BACKGROUNDLAYER_H
#define BACKGROUNDLAYER_H

#include "framework/Actor.h"

#include <string>

namespace ly
{
	class BackgroundLayer : public Actor
	{
	public:
		BackgroundLayer(World* owningWorld, 
			const List<std::string>& assetPaths = {},
			const sf::Vector2f& minVel = sf::Vector2f{ 0.0f, 50.0f },
			const sf::Vector2f& maxVel = sf::Vector2f{ 0.0f, 200.0f },
			float sizeMin = 1.0f,
			float sizeMax = 2.0f,
			int spriteCount = 20,
			const sf::Color& colorTint = sf::Color{180, 180, 200, 225}) noexcept;

		void SetAssets(const List<std::string>& assetPaths);
		void SetColorTint(const sf::Color& color);
		void SetSpriteCount(int newCount);

	private:
		void RefreshSprites();
		void RandomSpriteTexture(sf::Sprite& sprite);

		// randomY for when we are rendering transform of the sprite, do we want 
		// y position to be random? when they reach out of the window edge, we want
		// to random their poisition again but not on the y position
		void RandomSpriteTransform(sf::Sprite& sprite, bool randomY = false);
		void RandomSpritePosition(sf::Sprite& sprite, bool randomY);
		void RandomSpriteRotation(sf::Sprite& sprite);
		void RandomSpriteScale(sf::Sprite& sprite);


		shared<sf::Texture> GetRandomTexture() const;

	private:	
		sf::Vector2f m_MinVelocity;
		sf::Vector2f m_MaxVelocity;

		float m_SizeMin;
		float m_SizeMax;

		int m_SpriteCount;
		sf::Color m_TintColor;

		List<shared<sf::Texture>> m_Textures;
		List<sf::Sprite> m_Sprites;
		List<sf::Vector2f> m_Velocities;
	};
}

#endif // BACKGROUNDLAYER_H
