#include "framework/BackdropActor.h"
#include "framework/World.h"

namespace ly
{
	BackdropActor::BackdropActor(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity) noexcept
		: Actor{ owningWorld, texturePath },
		m_MovingVelocity{ velocity },
		m_LeftShift{ 0.0f },
		m_TopShift{ 0.0f }
	{
		auto windowSize = owningWorld->GetWorldSize();
		GetSprite().setOrigin(0.0f, 0.0f);
		GetSprite().setTextureRect(sf::IntRect{ sf::Vector2i{0, 0}, sf::Vector2i{static_cast<int>(windowSize.x), static_cast<int>(windowSize.y)} });
		SetTextureRepeated(true);
	}

	void BackdropActor::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		m_LeftShift += deltaTime * m_MovingVelocity.x;
		m_TopShift += deltaTime * m_MovingVelocity.y;

		// set the texture and determine how far we are shifting it
		sf::IntRect currentTextureRect = GetSprite().getTextureRect();
		currentTextureRect.left = m_LeftShift;
		currentTextureRect.top = m_TopShift;

		GetSprite().setTextureRect(currentTextureRect);
	}
}
