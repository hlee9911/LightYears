#pragma once
#ifndef GAMEPLAYHUD_H
#define GAMEPLAYHUD_H

#include "widgets/HUD.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGuage.h"

namespace ly
{
	class Actor;
	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD() noexcept;

		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void Tick(float deltaTime) override;


	private:
		virtual void Init(const sf::RenderWindow& windowRef) override;

		void RefreshHealthBar();
		void PlayerHealthUpdated(float changeAmt, float currentHealth, float maxHealth);
		void PlayerSpaceshipDestroyed(Actor* actor);

	private:
		TextWidget m_FrameRateText;
		ValueGuage m_PlayerHealthBar;

	};
}

#endif // GAMEPLAYHUD_H
