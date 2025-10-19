#pragma once
#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include "framework/Core.h"
#include "widgets/Widget.h"

#include <string>
#include <SFML/Graphics.hpp>

namespace ly
{
	class TextWidget : public Widget
	{
	public:
		TextWidget(const std::string& textStr, const std::string& fontPath =
			"SpaceShooterRedux/Bonus/kenvector_future.ttf",
			unsigned int characterSize = 10) noexcept;

		void SetTextString(const std::string& newString) noexcept;
		void SetTextSize(unsigned int newSize) noexcept;

	private:
		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void LocationUpdated(const sf::Vector2f& newLocation) override;
		virtual void RotationUpdated(float newRotation) override;

	private:
		shared<sf::Font> m_Font;
		sf::Text m_Text;

	};
}

#endif // TEXTWIDGET_H
