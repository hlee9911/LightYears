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
		m_ButtonHoverColor{ 190, 190, 190, 255 },
		m_IsButtonDown{ false }
	{
		m_ButtonSprite.setColor(m_ButtonDefaultColor);
		CenterText();
	}

	sf::FloatRect Button::GetBound() const
	{
		return m_ButtonSprite.getGlobalBounds();
	}

	bool Button::HandleEvent(const sf::Event& windowEvent)
	{
		bool handled = false;
		if (windowEvent.type == sf::Event::MouseButtonReleased)
		{
			if (windowEvent.mouseButton.button == sf::Mouse::Left)
			{
				// check if the mouse is inside the button bounds and make sure the button was pressed down
				if (m_ButtonSprite.getGlobalBounds().contains(windowEvent.mouseButton.x, windowEvent.mouseButton.y) &&
					m_IsButtonDown)
				{
					onButtonClicked.Broadcast();
					handled = true;
				}
			}
			ButtonUp();
		}
		// button down event
		else if (windowEvent.type == sf::Event::MouseButtonPressed)
		{
			if (m_ButtonSprite.getGlobalBounds().contains(windowEvent.mouseButton.x, windowEvent.mouseButton.y))
			{
				ButtonDown();
				handled = true;
			}
		}
		// button hover event
		else if (windowEvent.type == sf::Event::MouseMoved)
		{
			// if the left mouse button is not pressed, check for hover state
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (m_ButtonSprite.getGlobalBounds().contains(windowEvent.mouseMove.x, windowEvent.mouseMove.y))
				{
					MouseHovered();
				}
				else
				{
					ButtonUp();
				}
				handled = true;
			}
		}
		return handled || Widget::HandleEvent(windowEvent);
	}

	void Button::SetTextString(const std::string& newStr)
	{
		m_ButtonText.setString(newStr);
		CenterText();
	}

	void Button::SetTextSize(unsigned int newSize) noexcept
	{
		m_ButtonText.setCharacterSize(newSize);
		CenterText();
	}

	void Button::Draw(sf::RenderWindow& windowRef)
	{
		windowRef.draw(m_ButtonSprite);
		windowRef.draw(m_ButtonText);
	}

	void Button::LocationUpdated(const sf::Vector2f& newLocation)
	{
		m_ButtonSprite.setPosition(newLocation);
		CenterText();
	}

	void Button::RotationUpdated(float newRotation)
	{
		m_ButtonSprite.setRotation(newRotation);
		m_ButtonText.setRotation(newRotation);
	}

	void Button::CenterText()
	{
		sf::Vector2f widgetCenter = GetCenterPosition();
		sf::FloatRect textBounds = m_ButtonText.getGlobalBounds();
		m_ButtonText.setPosition(widgetCenter - sf::Vector2f{ textBounds.width / 2.0f, textBounds.height });
	}

	void Button::ButtonUp()
	{
		m_IsButtonDown = false;
		m_ButtonSprite.setColor(m_ButtonDefaultColor);
	}

	void Button::ButtonDown()
	{
		m_IsButtonDown = true;
		m_ButtonSprite.setColor(m_ButtonDownColor);
	}

	void Button::MouseHovered()
	{
		m_ButtonSprite.setColor(m_ButtonHoverColor);
	}
}
