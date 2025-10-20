#pragma once
#ifndef WIDGET_H
#define WIDGET_H

#include "framework/Object.h"

#include <SFML/Graphics.hpp>

namespace ly
{
	/// <summary>
	/// Base class for all UI widgets.
	/// </summary>
	class Widget : public Object
	{
	public:
		void NativeDraw(sf::RenderWindow& windowRef);
		virtual bool HandleEvent(const sf::Event& event);

		void SetWidgetLocation(const sf::Vector2f& newLocation);
		void SetWidgetRotation(float newRotation);
		sf::Vector2f GetWidgetLocation() const noexcept { return m_WidgetTransform.getPosition(); }
		float GetWidgetRotation() const noexcept { return m_WidgetTransform.getRotation(); }

		void SetVisibility(bool newVisibility) noexcept;
		bool IsVisible() const noexcept { return m_IsVisible; }
		virtual sf::FloatRect GetBound() const;
		sf::Vector2f GetCenterPosition() const;

	protected:
		Widget() noexcept;

	private:
		virtual void Draw(sf::RenderWindow& windowRef);
		virtual void LocationUpdated(const sf::Vector2f& newLocation);
		virtual void RotationUpdated(float newRotation);

	private:
		sf::Transformable m_WidgetTransform;
		bool m_IsVisible;

	};
}

#endif // WIDGET_H
