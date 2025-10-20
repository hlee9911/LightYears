#pragma once
#ifndef VALUEGUAGE_H
#define VALUEGUAGE_H

#include "widgets/Widget.h"

namespace ly
{
	class ValueGuage : public Widget
	{
	public:
		ValueGuage(const sf::Vector2f& size = sf::Vector2f{ 300.0f, 40.0f }, 
			float initialPercent = 0.75f, 
			const sf::Color& foregroundColor = sf::Color{ 128, 255, 128, 255 }, 
			const sf::Color& backgroundColor = sf::Color{ 128, 128, 128, 255 }) noexcept;

		void UpdateValue(float value, float maxValue);

		virtual sf::FloatRect GetBound() const override;
		
		void SetTextSize(unsigned int characterSize);

		void SetForegroundColor(const sf::Color& newColor) noexcept;
		void SetBackgroundColor(const sf::Color& newColor) noexcept;

	private:
		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void LocationUpdated(const sf::Vector2f& newLocation) override;
		virtual void RotationUpdated(float newRotation) override;
		void CenterText();

	private:
		shared<sf::Font> m_TextFont;
		sf::Text m_Text;

		sf::RectangleShape m_BarFront;
		sf::RectangleShape m_BarBack;

		sf::Color m_ForegroundColor;
		sf::Color m_BackgroundColor;

		float m_Percent;
	};
}

#endif // VALUEGUAGE_H
