#pragma once

#include "widgets/Widget.h"
#include "framework/Delegate.h"

#include <string>

namespace ly
{
	class Button : public Widget
	{
	public:
		Button(const std::string& textString = "Button", 
			const std::string& buttonTexturePath = "SpaceShooterRedux/PNG/UI/buttonBlue.png") noexcept;
		
		virtual sf::FloatRect GetBound() const override;
		virtual bool HandleEvent(const sf::Event& windowEvent) override;

		void SetTextString(const std::string& newStr);
		void SetTextSize(unsigned int newSize) noexcept;

		Delegate<> onButtonClicked;

	private:
		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void LocationUpdated(const sf::Vector2f& newLocation) override;
		virtual void RotationUpdated(float newRotation) override;

		void CenterText();

		void ButtonUp();
		void ButtonDown();
		void MouseHovered();

	private:
		shared<sf::Texture> m_ButtonTexture;
		sf::Sprite m_ButtonSprite;
	
		shared<sf::Font> m_ButtonFont;
		sf::Text m_ButtonText;

		sf::Color m_ButtonDefaultColor;
		sf::Color m_ButtonDownColor;
		sf::Color m_ButtonHoverColor;

		bool m_IsButtonDown;
	};
}
