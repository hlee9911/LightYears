#include "framework/BackgroundLayer.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"

namespace ly
{
	BackgroundLayer::BackgroundLayer(World* owningWorld, 
		const List<std::string>& assetPaths, 
		const sf::Vector2f& minVel, 
		const sf::Vector2f& maxVel, 
		float sizeMin, 
		float sizeMax, 
		int spriteCount,
		const sf::Color& colorTint) noexcept
		: Actor{ owningWorld },
		m_MinVelocity{ minVel },
		m_MaxVelocity{ maxVel },
		m_SizeMin{ sizeMin },
		m_SizeMax{ sizeMax },
		m_SpriteCount{ spriteCount },
		m_TintColor{ colorTint }
	{
		SetAssets(assetPaths);
		SetEnablePhysics(false);
	}

	void BackgroundLayer::SetAssets(const List<std::string>& assetPaths)
	{
		for (const std::string& texturePath : assetPaths)
		{
			shared<sf::Texture> newTexture = AssetManager::Get().LoadTexture(texturePath);
			m_Textures.push_back(newTexture);
		}
	}

	void BackgroundLayer::SetColorTint(const sf::Color& color)
	{
		m_TintColor = color;
		for (auto& sprite : m_Sprites)
		{
			sprite.setColor(color);
		}
	}

	void BackgroundLayer::SetSpriteCount(int newCount)
	{
		m_SpriteCount = newCount;
		RefreshSprites();
	}

	void BackgroundLayer::RefreshSprites()
	{
		m_Sprites.clear();
		m_Velocities.clear();

		for (int i = 0; i < m_SpriteCount; ++i)
		{
			sf::Sprite newSprite{};
			RandomSpriteTexture(newSprite);
			RandomSpriteTransform(newSprite, true);
			m_Sprites.push_back(newSprite);

			float velX = RandomRange(m_MinVelocity.x, m_MaxVelocity.x);
			float velY = RandomRange(m_MinVelocity.y, m_MaxVelocity.y);
			m_Velocities.push_back(sf::Vector2f{ velX, velY });
		}

		SetColorTint(m_TintColor);
	}

	void BackgroundLayer::RandomSpriteTexture(sf::Sprite& sprite)
	{
		if (m_Textures.size() > 0)
		{
			shared<sf::Texture> pickedTexture = GetRandomTexture();
			sprite.setTexture(*(pickedTexture.get()));
			sprite.setTextureRect(sf::IntRect{ 0, 0, static_cast<int>(pickedTexture->getSize().x), static_cast<int>(pickedTexture->getSize().y) });
			sf::FloatRect bound = sprite.getGlobalBounds();
			sprite.setOrigin(bound.width / 2.0f, bound.height / 2.0f);
		}
	}

	void BackgroundLayer::RandomSpriteTransform(sf::Sprite& sprite, bool randomY)
	{
		RandomSpritePosition(sprite, randomY);
		RandomSpriteRotation(sprite);
		RandomSpriteScale(sprite);
	}

	void BackgroundLayer::RandomSpritePosition(sf::Sprite& sprite, bool randomY)
	{
		auto windowSize = GetWorld()->GetWorldSize();
		auto bound = sprite.getGlobalBounds();

		float posX = RandomRange(0, windowSize.x);
		float posY = randomY ? RandomRange(0, windowSize.y) : -bound.height;

		sprite.setPosition(sf::Vector2f{posX, posY});
	}

	void BackgroundLayer::RandomSpriteRotation(sf::Sprite& sprite)
	{
		sprite.setRotation(RandomRange(0, 360.0f));
	}

	void BackgroundLayer::RandomSpriteScale(sf::Sprite& sprite)
	{
		float size = RandomRange(m_SizeMax, m_SizeMax);
		sprite.setScale(size, size);
	}

	shared<sf::Texture> BackgroundLayer::GetRandomTexture() const
	{
		int randomPickIndex = static_cast<int>(RandomRange(0, m_Textures.size()));
		return m_Textures[randomPickIndex];
	}
}
