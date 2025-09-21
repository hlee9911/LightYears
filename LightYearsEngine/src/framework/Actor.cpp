#include "framework/Actor.h"
#include "framework/Core.h"

namespace ly
{
	Actor::Actor(World* owningWorld, const std::string& texturePath) noexcept
		: m_OwningWorld{ owningWorld },
		m_HasBegunPlay{ false },
		m_Sprite{},
		m_Texture{}
	{
		SetTexture(texturePath);
	}

	Actor::~Actor() noexcept
	{
		LOG("Actor Destroyed");
	}

	void Actor::BeginPlayInternal()
	{
		if (!m_HasBegunPlay)
		{
			m_HasBegunPlay = true;
			BeginPlay();
		}
	}

	void Actor::TickInternal(float deltaTime)
	{
		if (IsPendingDestroy()) return;

		Tick(deltaTime);
	}

	void Actor::BeginPlay()
	{
		LOG("Actor begin play");
	}

	void Actor::Tick(float deltaTime)
	{
		LOG("Actor ticking at frame rate: %f", 1.0f / deltaTime);
	}

	void Actor::SetTexture(const std::string& texturePath)
	{
		m_Texture.loadFromFile(texturePath);
		m_Sprite.setTexture(m_Texture);

		int textureWidth = m_Texture.getSize().x;
		int textureHeight = m_Texture.getSize().y;
		// Set the texture rectangle to match the texture size
		m_Sprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{textureWidth, textureHeight} });
	}

	void Actor::Render(sf::RenderWindow& window)
	{
		if (IsPendingDestroy()) return;

		window.draw(m_Sprite);
	}
}
