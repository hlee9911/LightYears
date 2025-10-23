#pragma once
#ifndef MAINMENUHUD_H
#define MAINMENUHUD_H

#include "widgets/HUD.h"
#include "widgets/Button.h"
#include "widgets/TextWidget.h"

namespace ly
{
	class MainMenuHUD : public HUD
	{
	public:
		MainMenuHUD() noexcept;

		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual bool HandleEvent(const sf::Event& event) override;

		Delegate<> onStartButtonClicked;
		Delegate<> onQuitButtonClicked;

	private:
		virtual void Init(const sf::RenderWindow& windowRef) override;
		void StartButtonClicked();
		void QuitButtonClicked();

	private:
		TextWidget m_TitleText;
		Button m_StartButton;
		Button m_QuitButton;
	};
}

#endif // MAINMENUHUD_H
