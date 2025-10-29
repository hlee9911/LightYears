#include "level/MainMenuLevel.h"
#include "level/GameLevelOne.h"
#include "widgets/MainMenuHUD.h"
#include "framework/Application.h"
#include "framework/BackdropActor.h"

namespace ly
{
	MainMenuLevel::MainMenuLevel(Application* owningApp) noexcept
		: World{ owningApp }
	{
		m_MainMenuHUD = SpawnHUD<MainMenuHUD>();
	}

	void MainMenuLevel::BeginPlay()
	{
		m_MainMenuHUD.lock()->onStartButtonClicked.BindAction(GetWeakRef(), &MainMenuLevel::StartGame);
		m_MainMenuHUD.lock()->onQuitButtonClicked.BindAction(GetWeakRef(), &MainMenuLevel::QuitGame);
		SpawnActor<BackdropActor>("SpaceShooterRedux/mainMenuBg.png", sf::Vector2f{0.0f, 0.0f});
	}

	void MainMenuLevel::StartGame()
	{
		GetOwningApplication()->LoadWorld<GameLevelOne>();
		// LOG("Starting Game");
	}

	void MainMenuLevel::QuitGame()
	{
		// LOG("Quitting Game");
		GetOwningApplication()->QuitApplication();
	}
}
