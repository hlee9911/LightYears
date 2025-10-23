#include "widgets/MainMenuHUD.h"

namespace ly
{
	MainMenuHUD::MainMenuHUD() noexcept
		: HUD{},
		m_TitleText{ "Light Years" },
		m_StartButton{ "Start" },
		m_QuitButton{ "Quit" }
	{
		m_TitleText.SetTextSize(40);
		m_StartButton.SetTextSize(20);
		m_QuitButton.SetTextSize(20);
	}

	void MainMenuHUD::Draw(sf::RenderWindow& windowRef)
	{
		m_TitleText.NativeDraw(windowRef);
		m_StartButton.NativeDraw(windowRef);
		m_QuitButton.NativeDraw(windowRef);
	}

	bool MainMenuHUD::HandleEvent(const sf::Event& event)
	{
		return m_StartButton.HandleEvent(event) ||
			   m_QuitButton.HandleEvent(event) ||
			   HUD::HandleEvent(event);
	}

	void MainMenuHUD::Init(const sf::RenderWindow& windowRef)
	{
		sf::Vector2u windowSize = windowRef.getSize();
		m_TitleText.SetWidgetLocation({ windowSize.x / 2.0f - m_TitleText.GetBound().width / 2.0f, 100.0f});

		m_StartButton.SetWidgetLocation({ windowSize.x / 2.0f - m_StartButton.GetBound().width / 2.0f, windowSize.y / 2.0f});
		m_QuitButton.SetWidgetLocation(m_StartButton.GetWidgetLocation() + sf::Vector2f{ 0.0f, 50.0f });
	
		m_StartButton.onButtonClicked.BindAction(GetWeakRef(), &MainMenuHUD::StartButtonClicked);
		m_QuitButton.onButtonClicked.BindAction(GetWeakRef(), &MainMenuHUD::QuitButtonClicked);
	}

	void MainMenuHUD::StartButtonClicked()
	{
		onStartButtonClicked.Broadcast();
	}

	void MainMenuHUD::QuitButtonClicked()
	{
		onQuitButtonClicked.Broadcast();
	}
}
