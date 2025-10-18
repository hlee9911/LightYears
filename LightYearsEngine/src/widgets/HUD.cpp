#include "widgets/HUD.h"

namespace ly
{
	void HUD::NativeInit(const sf::RenderWindow& windowRef)
	{
		if (!m_AlreadyInit)
		{
			m_AlreadyInit = true;
			Init(windowRef);
		}
	}

	bool HUD::HandleEvent(const sf::Event& event)
	{
		return false;
	}

	HUD::HUD() noexcept
		: m_AlreadyInit{ false }
	{

	}

	void HUD::Init(const sf::RenderWindow& windowRef)
	{

	}
}
