#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "player/PlayerSpaceship.h"
#include "config.h"

ly::Application* GetApplication()
{
	return new ly::GameApplication{};
}

namespace ly
{
	GameApplication::GameApplication() noexcept
		: Application{ 600, 980, "Light Years", sf::Style::Titlebar | sf::Style::Close}
	{
		// Set the asset root directory for the AssetManager
		AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
		
		weak<World> newWorld = LoadWorld<World>();
		// newWorld.lock()->SpawnActor<Actor>();
		m_TestPlayerSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceship>();
		// m_TestPlayerSpaceship.lock()->SetTexture(GetResourceDir() + "SpaceShooterRedux/PNG/playerShip1_blue.png");
		m_TestPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f{ 300.0f, 490.0f });
		// m_TestPlayerSpaceship.lock()->SetActorRotation(90.0f);
		m_Counter = 0.0f;

		weak<Spaceship> testSpaceship = newWorld.lock()->SpawnActor<Spaceship>();
		testSpaceship.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip1_red.png");
		testSpaceship.lock()->SetActorLocation(sf::Vector2f{ 100.0f, 50.0f });

		m_Counter = 0.0f;
	}

	void GameApplication::Tick(float deltaTime)
	{
		m_Counter += deltaTime;
		if (m_Counter >= 10.0f)
		{
			if (!m_TestPlayerSpaceship.expired())
			{
				m_TestPlayerSpaceship.lock()->Destroy();
				// LOG("Actor marked for destruction");
			}
		}
	}
}
