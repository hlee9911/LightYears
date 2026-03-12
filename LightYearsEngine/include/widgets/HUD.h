#pragma once

#include <SFML/Graphics.hpp>

#include "framework/Object.h"

namespace ly
{
	class HUD : public Object
	{
	public:
		virtual void Draw(sf::RenderWindow& windowRef) = 0;
		void NativeInit(const sf::RenderWindow& windowRef);
		bool HasInit() const noexcept { return m_AlreadyInit; }
		virtual bool HandleEvent(const sf::Event& event);
		virtual void Tick(float deltaTime);

	protected:
		HUD() noexcept;

	private:
		virtual void Init(const sf::RenderWindow& windowRef);
	
	private:
		bool m_AlreadyInit;
	};
}
