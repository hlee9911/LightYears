#pragma once
#ifndef GAMEPLAYHUD_H
#define GAMEPLAYHUD_H

#include "widgets/HUD.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGuage.h"
#include "widgets/ImageWidget.h"
#include "widgets/Button.h"

#include <string>

namespace ly
{
	class Actor;
	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD() noexcept;

		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void Tick(float deltaTime) override;
		virtual bool HandleEvent(const sf::Event& event) override;

		void GameFinished(bool playerWon);

		Delegate<> onRestartButtonClicked;
		Delegate<> onQuitButtonClicked;

	private:
		virtual void Init(const sf::RenderWindow& windowRef) override;

		void RefreshHealthBar();
		void ConnectPlayerStatus();
		void PlayerHealthUpdated(float changeAmt, float currentHealth, float maxHealth);
		void PlayerLifeCountUpdated(int changeAmt);
		void PlayerScoreUpdated(int newScore);
		void PlayerSpaceshipDestroyed(Actor* actor);

		void RestartButtonClicked();
		void QuitButtonClicked();
		
		std::string FormatWithCommas(int value);

	private:
		TextWidget m_FrameRateText;
		ValueGuage m_PlayerHealthBar;
		ImageWidget m_PlayerLifeIcon;
		TextWidget m_PlayerLivesText;

		ImageWidget m_PlayerScoreIcon;
		TextWidget m_PlayerScoreText;

		sf::Color m_HealthyHealthBarColor;
		sf::Color m_WarningHealthBarColor;
		sf::Color m_DangerHealthBarColor;

		float m_HealthWarningThreshold;
		float m_HealthDangerThreshold;

		float m_WidgetSpacing;

		TextWidget m_WinLoseText;
		TextWidget m_FinalScoreText;
		Button m_RestartButton;
		Button m_QuitButton;
	};
}

#endif // GAMEPLAYHUD_H
