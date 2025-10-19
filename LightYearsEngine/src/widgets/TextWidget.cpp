#include "widgets/TextWidget.h"
#include "framework/AssetManager.h"

namespace ly
{
	TextWidget::TextWidget(const std::string& textStr, const std::string& fontPath, unsigned int characterSize) noexcept
		: m_Font{ AssetManager::Get().LoadFont(fontPath) },
		m_Text{ textStr, *(m_Font.get()), characterSize }
	{

	}

	void TextWidget::SetTextString(const std::string& newString) noexcept
	{
		m_Text.setString(newString);
	}

	void TextWidget::SetTextSize(unsigned int newSize) noexcept
	{
		m_Text.setCharacterSize(newSize);
	}

	void TextWidget::Draw(sf::RenderWindow& windowRef)
	{
		windowRef.draw(m_Text);
	}

	void TextWidget::LocationUpdated(const sf::Vector2f& newLocation)
	{
		m_Text.setPosition(newLocation);
	}

	void TextWidget::RotationUpdated(float newRotation)
	{
		m_Text.setRotation(newRotation);
	}
}
