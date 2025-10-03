#include "level/GameLevelOne.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/TimerManager.h"
#include "player/PlayerSpaceship.h"
#include "enemy/Vanguard.h"

namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp) noexcept
		: World{ owningApp }
	{
		m_TestPlayerSpaceship = SpawnActor<PlayerSpaceship>();
		m_TestPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f{ 300.0f, 490.0f });
		// m_TestPlayerSpaceship.lock()->SetActorRotation(-90.0f);

		weak<Vanguard> testSpaceship = SpawnActor<Vanguard>();
		testSpaceship.lock()->SetActorLocation(sf::Vector2f{ 100.0f, 50.0f });
	}

	void GameLevelOne::BeginPlay()
	{
		TimerManager::Get().SetTimer(GetWeakRef(), &GameLevelOne::TimerCallBack_Test, 10.0f);
	}

	void GameLevelOne::TimerCallBack_Test()
	{

	}


}
