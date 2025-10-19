#include "widgets/Widget.h"

namespace ly
{
	void Widget::NativeDraw(sf::RenderWindow& windowRef)
	{
		if (m_IsVisible)
		{
			Draw(windowRef);
		}
	}

	bool Widget::HandleEvent(const sf::Event& event)
	{
		return false;
	}

	void Widget::SetWidgetLocation(const sf::Vector2f& newLocation)
	{
		m_WidgetTransform.setPosition(newLocation);
		LocationUpdated(newLocation);
	}

	void Widget::SetWidgetRotation(float newRotation)
	{
		m_WidgetTransform.setRotation(newRotation);
		RotationUpdated(newRotation);
	}

	void Widget::SetVisibility(bool newVisibility) noexcept
	{
		m_IsVisible = newVisibility;
	}

	Widget::Widget() noexcept
		: m_IsVisible{ true },
		m_WidgetTransform{}
	{

	}

	void Widget::Draw(sf::RenderWindow& windowRef)
	{

	}

	void Widget::LocationUpdated(const sf::Vector2f& newLocation)
	{

	}

	void Widget::RotationUpdated(float newRotation)
	{

	}
}
