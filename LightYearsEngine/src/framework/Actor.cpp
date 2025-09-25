#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"

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
		// LOG("Actor Destroyed");
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
		// LOG("Actor begin play");
	}

	void Actor::Tick(float deltaTime)
	{
		// LOG("Actor ticking at frame rate: %f", 1.0f / deltaTime);
	}

	void Actor::SetTexture(const std::string& texturePath)
	{
		m_Texture = AssetManager::Get().LoadTexture(texturePath);
		if (!m_Texture) return;
		m_Sprite.setTexture(*m_Texture);

		int textureWidth = m_Texture->getSize().x;
		int textureHeight = m_Texture->getSize().y;
		// Set the texture rectangle to match the texture size
		m_Sprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{textureWidth, textureHeight} });
		CenterPivot();
	}

	void Actor::Render(sf::RenderWindow& window)
	{
		if (IsPendingDestroy()) return;

		window.draw(m_Sprite);
	}

	// Transformations

	void Actor::SetActorLocation(const sf::Vector2f& newLoc)
	{
		m_Sprite.setPosition(newLoc);
	}

	void Actor::SetActorRotation(float newRot)
	{
		m_Sprite.setRotation(newRot);
	}

	void Actor::SetActorScale(const sf::Vector2f& newScale)
	{
		m_Sprite.setScale(newScale);
	}

	void Actor::AddActorLocationOffset(const sf::Vector2f& offsetAmt)
	{
		SetActorLocation(GetActorLocation() + offsetAmt);
	}

	void Actor::AddActorRotationOffset(float offsetAmt)
	{
		SetActorRotation(GetActorRotation() + offsetAmt);
	}

	sf::Vector2f Actor::GetActorLocation() const
	{
		return m_Sprite.getPosition();
	}

	float Actor::GetActorRotation() const
	{
		return m_Sprite.getRotation();
	}

	sf::Vector2f Actor::GetActorScale() const
	{
		return m_Sprite.getScale();
	}

	sf::Vector2f Actor::GetActorForwardDirection() const
	{
		return RotationToVector(GetActorRotation() + 270.0f);
	}

	sf::Vector2f Actor::GetActorRightDirection() const
	{
		return RotationToVector(GetActorRotation());
	}

	sf::Vector2u Actor::GetWindowSize() const noexcept
	{
		return m_OwningWorld->GetWorldSize();
	}

	// make the pivot point the center of the sprite
	void Actor::CenterPivot()
	{
		if (!m_Texture) return;
		sf::FloatRect spriteBound = m_Sprite.getGlobalBounds();
		m_Sprite.setOrigin(spriteBound.width / 2.0f, spriteBound.height / 2.0f);
	}
}
