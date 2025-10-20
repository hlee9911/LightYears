#include "widgets/ValueGuage.h"
#include "framework/AssetManager.h"

#include <string>

namespace ly
{
	ValueGuage::ValueGuage(const sf::Vector2f& size, float initialPercent, const sf::Color& foregroundColor, const sf::Color& backgroundColor) noexcept
		: m_TextFont{ AssetManager::Get().LoadFont("SpaceShooterRedux/Bonus/kenvector_future.ttf") },
		m_Text{ "", *(m_TextFont.get()) },
		m_BarFront{ size },
		m_BarBack{ size },
		m_Percent{ initialPercent },
		m_ForegroundColor{ foregroundColor },
		m_BackgroundColor{ backgroundColor }
	{
		m_BarFront.setFillColor(m_ForegroundColor);
		m_BarBack.setFillColor(m_BackgroundColor);
		SetTextSize(25);
	}

	void ValueGuage::UpdateValue(float value, float maxValue)
	{
		if (maxValue == 0) return;
		m_Percent = value / maxValue;
		std::string displayStr = std::to_string(static_cast<int>(value)) + "/" + std::to_string(static_cast<int>(maxValue));
		m_Text.setString(displayStr);

		sf::Vector2f barSize = m_BarBack.getSize();
		m_BarFront.setSize({barSize.x * m_Percent, barSize.y});
		CenterText();
	}

	sf::FloatRect ValueGuage::GetBound() const
	{
		return m_BarBack.getGlobalBounds();
	}

	void ValueGuage::SetTextSize(unsigned int characterSize)
	{
		m_Text.setCharacterSize(characterSize);
		CenterText();
	}

	void ValueGuage::SetForegroundColor(const sf::Color& newColor) noexcept
	{
		m_BarFront.setFillColor(newColor);
	}

	void ValueGuage::SetBackgroundColor(const sf::Color& newColor) noexcept
	{
		m_BarBack.setFillColor(newColor);
	}

	void ValueGuage::Draw(sf::RenderWindow& windowRef)
	{
		windowRef.draw(m_BarBack);
		windowRef.draw(m_BarFront);
		windowRef.draw(m_Text);
	}

	void ValueGuage::LocationUpdated(const sf::Vector2f& newLocation)
	{
		m_Text.setPosition(newLocation);
		m_BarFront.setPosition(newLocation);
		m_BarBack.setPosition(newLocation);
		CenterText();
	}

	void ValueGuage::RotationUpdated(float newRotation)
	{
		m_Text.setRotation(newRotation);
		m_BarFront.setRotation(newRotation);
		m_BarBack.setRotation(newRotation);
	}

	void ValueGuage::CenterText()
	{
		sf::Vector2f widgetCenter = GetCenterPosition();
		sf::FloatRect textBounds = m_Text.getGlobalBounds();
		m_Text.setPosition(widgetCenter - sf::Vector2f{ textBounds.width / 2.0f, textBounds.height });
	}
}
