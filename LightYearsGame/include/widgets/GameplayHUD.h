#pragma once
#ifndef GAMEPLAYHUD_H
#define GAMEPLAYHUD_H

#include "widgets/HUD.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGuage.h"
#include "widgets/ImageWidget.h"

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
		void ConnectPlayerLifeCount();
		void PlayerHealthUpdated(float changeAmt, float currentHealth, float maxHealth);
		void PlayerLifeCountUpdated(int changeAmt);
		void PlayerSpaceshipDestroyed(Actor* actor);

	private:
		TextWidget m_FrameRateText;
		ValueGuage m_PlayerHealthBar;
		ImageWidget m_PlayerLifeIcon;
		TextWidget m_PlayerLivesText;

		sf::Color m_HealthyHealthBarColor;
		sf::Color m_WarningHealthBarColor;
		sf::Color m_DangerHealthBarColor;

		float m_HealthWarningThreshold;
		float m_HealthDangerThreshold;

		float m_WidgetSpacing;
	};
}

#endif // GAMEPLAYHUD_H
