#include "level/GameLevelOne.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/Application.h"
#include "framework/BackdropActor.h"
#include "framework/BackgroundLayer.h"
#include "framework/TimerManager.h"
#include "player/PlayerSpaceship.h"
#include "enemy/Vanguard.h"
#include "enemy/VanguardStage.h"
#include "enemy/TwinBlade.h"
#include "enemy/TwinBladeStage.h"
#include "enemy/Hexagon.h"
#include "enemy/HexagonStage.h"
#include "enemy/UFO.h"
#include "enemy/UFOStage.h"
#include "enemy/ChaosStage.h"
#include "enemy/Boss.h"
#include "enemy/BossStage.h"
#include "gameplay/GameStage.h"
#include "gameplay/WaitStage.h"
#include "player/PlayerManager.h"
#include "widgets/GameplayHUD.h"

namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp) noexcept
		: World{ owningApp },
		m_TimerHandle_Test{}
	{

	}

	void GameLevelOne::AllGameStagesFinished()
	{
		m_GameplayHUD.lock()->GameFinished(true);
	}

	void GameLevelOne::BeginPlay()
	{
		SpawnCosmetics();

		Player& newPlayer = PlayerManager::Get().CreateNewPlayer();
		m_PlayerSpaceship = newPlayer.SpawnSpaceship(this);
		m_PlayerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
		
		m_GameplayHUD = SpawnHUD<GameplayHUD>();
		m_GameplayHUD.lock()->onQuitButtonClicked.BindAction(GetWeakRef(), &GameLevelOne::QuitGame);
		m_GameplayHUD.lock()->onRestartButtonClicked.BindAction(GetWeakRef(), &GameLevelOne::RestartGame);

		// m_TimerHandle_Test = TimerManager::Get().SetTimer(GetWeakRef(), &GameLevelOne::TimerCallBack_Test, 2.0f, true);
		//weak<UFO> testUFO = SpawnActor<UFO>(sf::Vector2f{ 0.0f, 0.0f });
		//testUFO.lock()->SetActorLocation(sf::Vector2f{ GetWorldSize().x / 2.0f, GetWorldSize().y / 2.0f });
	}

	// for debugging purpose
	//void GameLevelOne::TimerCallBack_Test()
	//{
	//	LOG("Callback called");
	//	TimerManager::Get().ClearTimer(m_TimerHandle_Test);
	//}

	void GameLevelOne::PlayerSpaceshipDestroyed(Actor* destroyedPlayerSpaceship)
	{
		m_PlayerSpaceship = PlayerManager::Get().GetPlayer()->SpawnSpaceship(this);
		if (!m_PlayerSpaceship.expired())
		{
			// subscribe to onActorDestroyed again as long as the player still has the life count left
			m_PlayerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
		}
		else
		{
			GameOver();
		}
	}

	void GameLevelOne::QuitGame()
	{
		GetOwningApplication()->QuitApplication();
	}

	void GameLevelOne::RestartGame()
	{
		PlayerManager::Get().Reset();
		GetOwningApplication()->LoadWorld<GameLevelOne>();
	}

	void GameLevelOne::GameOver()
	{
		LOG("======================= Game Over! =======================");
		if (!m_GameplayHUD.expired())
		{
			m_GameplayHUD.lock()->GameFinished(false);
		}
	}

	void GameLevelOne::SpawnCosmetics()
	{
		auto backdropActor = SpawnActor<BackdropActor>("SpaceShooterRedux/Backgrounds/darkPurple.png");
		weak<BackgroundLayer> planets = SpawnActor<BackgroundLayer>();
		planets.lock()->SetAssets(
			{
				"SpaceShooterRedux/PNG/Planets/Planet1.png",
				"SpaceShooterRedux/PNG/Planets/Planet2.png",
				"SpaceShooterRedux/PNG/Planets/Planet3.png",
				"SpaceShooterRedux/PNG/Planets/planet4.png",
				"SpaceShooterRedux/PNG/Planets/planet5.png",
				"SpaceShooterRedux/PNG/Planets/planet6.png",
				"SpaceShooterRedux/PNG/Planets/planet7.png"
			}
		);
		planets.lock()->SetSpriteCount(1);
		planets.lock()->SetSizes(0.8f, 1.25f);
		planets.lock()->SetVelocities({0.0f, 50.0f}, {0.0f, 100.0f});

		weak<BackgroundLayer> meteors = SpawnActor<BackgroundLayer>();
		meteors.lock()->SetAssets(
			{
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big3.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big4.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_med1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_med3.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_small1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_small2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_tiny1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_tiny2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big3.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big4.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_med1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_med2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_small1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_small2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_tiny1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_tiny2.png",
			}
		);
		meteors.lock()->SetSpriteCount(20);
		meteors.lock()->SetSizes(0.2f, 0.5f);
		// meteors.lock()->SetVelocities({ 0.0f, 5.0f }, { 0.0f, 100.0f });
	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(shared<WaitStage>{ new WaitStage{ this, 0.5f } });
		AddStage(shared<VanguardStage>{ new VanguardStage{this} });

		AddStage(shared<WaitStage>{ new WaitStage{ this, 4.0f } });
		AddStage(shared<TwinBladeStage>{ new TwinBladeStage{ this } });

		AddStage(shared<WaitStage>{ new WaitStage{ this, 4.0f } });
		AddStage(shared<HexagonStage>{ new HexagonStage{ this } });

		AddStage(shared<WaitStage>{ new WaitStage{ this, 4.0f } });
		AddStage(shared<UFOStage>{ new UFOStage{ this } });

		AddStage(shared<WaitStage>{ new WaitStage{ this, 0.5f } });
		AddStage(shared<ChaosStage>{ new ChaosStage{ this } });

		AddStage(shared<WaitStage>{ new WaitStage{ this, 2.0f } });
		AddStage(shared<BossStage>{ new BossStage{ this } });
	}
}
