#include "level/GameLevelOne.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/TimerManager.h"
#include "player/PlayerSpaceship.h"
#include "enemy/Vanguard.h"
#include "enemy/VanguardStage.h"
#include "enemy/TwinBlade.h"
#include "enemy/TwinBladeStage.h"
#include "enemy/Hexagon.h"
#include "enemy/HexagonStage.h"
#include "gameplay/GameStage.h"
#include "gameplay/WaitStage.h"

namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp) noexcept
		: World{ owningApp },
		m_TimerHandle_Test{}
	{
		m_TestPlayerSpaceship = SpawnActor<PlayerSpaceship>();
		m_TestPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f{ 300.0f, 490.0f });
		// m_TestPlayerSpaceship.lock()->SetActorRotation(-90.0f);

		// for testing
		//weak<Vanguard> testSpaceship = SpawnActor<Vanguard>();
		//testSpaceship.lock()->SetActorLocation(sf::Vector2f{ 100.0f, 50.0f });
	}

	void GameLevelOne::BeginPlay()
	{
		// m_TimerHandle_Test = TimerManager::Get().SetTimer(GetWeakRef(), &GameLevelOne::TimerCallBack_Test, 2.0f, true);
	}

	// for debugging purpose
	//void GameLevelOne::TimerCallBack_Test()
	//{
	//	LOG("Callback called");
	//	TimerManager::Get().ClearTimer(m_TimerHandle_Test);
	//}

	void GameLevelOne::InitGameStages()
	{
		// AddStage(shared<WaitStage>{ new WaitStage{ this, 2.0f } });
		AddStage(shared<HexagonStage>{ new HexagonStage{ this } });
		AddStage(shared<WaitStage>{ new WaitStage{ this, 4.0f } });
		AddStage(shared<VanguardStage>{ new VanguardStage{this} });
		AddStage(shared<WaitStage>{ new WaitStage{ this, 4.0f } });
		AddStage(shared<TwinBladeStage>{ new TwinBladeStage{ this } });
	}

}
