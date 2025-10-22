#include "widgets/Button.h"
#include "framework/AssetManager.h"

namespace ly
{
	Button::Button(const std::string& textString, const std::string& buttonTexturePath) noexcept
		: m_ButtonTexture{ AssetManager::Get().LoadTexture(buttonTexturePath) },
		m_ButtonSprite{ *(m_ButtonTexture.get()) },
		m_ButtonFont{ AssetManager::Get().LoadFont("SpaceShooterRedux/Bonus/kenvector_future.ttf") },
		m_ButtonText{ textString, *(m_ButtonFont.get()) },
		m_ButtonDefaultColor{ 128, 128, 128, 255 },
		m_ButtonDownColor{ 64, 64, 64, 255 },
		m_ButtonHoverColor{ 192, 192, 192, 255 },
		m_IsButtonDown{ false }
	{

	}

	sf::FloatRect Button::GetBound() const
	{
		return m_ButtonSprite.getGlobalBounds();
	}

	void Button::Draw(sf::RenderWindow& windowRef)
	{
		windowRef.draw(m_ButtonSprite);
		windowRef.draw(m_ButtonText);
	}

	void Button::LocationUpdated(const sf::Vector2f& newLocation)
	{
		m_ButtonSprite.setPosition(newLocation);
		m_ButtonText.setPosition(newLocation);
	}

	void Button::RotationUpdated(float newRotation)
	{
		m_ButtonSprite.setRotation(newRotation);
		m_ButtonText.setRotation(newRotation);
	}
}
