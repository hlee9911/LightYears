#include "widgets/ImageWidget.h"
#include "framework/AssetManager.h"

namespace ly
{
	ImageWidget::ImageWidget(const std::string& imagePath) noexcept
		: m_Texture{AssetManager::Get().LoadTexture(imagePath)},
		m_Sprite{*(m_Texture.get())}
	{

	}

	void ImageWidget::SetImage(const shared<sf::Texture>& newTexture)
	{
		if (newTexture)
		{
			m_Texture = newTexture;
			m_Sprite.setTexture(*(m_Texture.get()));
		}
	}

	sf::FloatRect ImageWidget::GetBound() const
	{
		return m_Sprite.getGlobalBounds();
	}

	void ImageWidget::LocationUpdated(const sf::Vector2f& newLocation)
	{
		m_Sprite.setPosition(newLocation);
	}

	void ImageWidget::RotationUpdated(float newRotation)
	{
		m_Sprite.setRotation(newRotation);
	}

	void ImageWidget::Draw(sf::RenderWindow& windowRef)
	{
		windowRef.draw(m_Sprite);
	}
}
