#pragma once
#ifndef GAMEPLAYHUD_H
#define GAMEPLAYHUD_H

#include "widgets/HUD.h"
#include "widgets/TextWidget.h"

namespace ly
{
	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD() noexcept;

		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void Tick(float deltaTime) override;

	private:
		TextWidget m_FrameRateText;

	};
}

#endif // GAMEPLAYHUD_H
