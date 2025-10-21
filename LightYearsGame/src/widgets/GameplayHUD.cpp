#include "widgets/GameplayHUD.h"
#include "framework/Actor.h"
#include "player/PlayerSpaceship.h"
#include "player/PlayerManager.h"
#include "player/Player.h"

namespace ly
{
	GameplayHUD::GameplayHUD() noexcept
		: HUD{},
		m_FrameRateText{ "FPS: " },
		m_PlayerHealthBar{},
		m_PlayerLifeIcon{ "SpaceShooterRedux/PNG/pickups/playerLife1_blue.png" },
		m_PlayerLivesText{ "" },
		m_HealthyHealthBarColor{ sf::Color{ 128, 255, 128, 255 } },
		m_WarningHealthBarColor{ sf::Color{ 255, 255, 0, 255 } },
		m_DangerHealthBarColor{ sf::Color{ 255, 0, 0, 255 } },
		m_HealthWarningThreshold{ 0.7f },
		m_HealthDangerThreshold{ 0.3f },
		m_WidgetSpacing{ 10.0f }
	{
		m_FrameRateText.SetTextSize(25);
		m_PlayerLivesText.SetTextSize(20);
	}

	void GameplayHUD::Draw(sf::RenderWindow& windowRef)
	{
		m_FrameRateText.NativeDraw(windowRef);
		m_PlayerHealthBar.NativeDraw(windowRef);
		m_PlayerLifeIcon.NativeDraw(windowRef);
		m_PlayerLivesText.NativeDraw(windowRef);
	}

	void GameplayHUD::Tick(float deltaTime)
	{
		int frameRate = static_cast<int>(1.0f / deltaTime);
		std::string frameRateStr = "FPS: " + std::to_string(frameRate);
		m_FrameRateText.SetTextString(frameRateStr);
	}

	void GameplayHUD::Init(const sf::RenderWindow& windowRef)
	{
		auto windowSize = windowRef.getSize();
		m_PlayerHealthBar.SetWidgetLocation(sf::Vector2f{ 20.0f, windowSize.y - 50.0f });
		
		sf::Vector2f nextWidgetPos = m_PlayerHealthBar.GetWidgetLocation();

		// position the life icon next to the health bar
		nextWidgetPos += sf::Vector2f{ m_PlayerHealthBar.GetBound().width + m_WidgetSpacing, 7.5f };
		m_PlayerLifeIcon.SetWidgetLocation(nextWidgetPos);

		// position the life count text next to the life icon
		nextWidgetPos += sf::Vector2f{ m_PlayerLifeIcon.GetBound().width + m_WidgetSpacing, 0.0f };
		m_PlayerLivesText.SetWidgetLocation(nextWidgetPos);

		RefreshHealthBar();
		ConnectPlayerLifeCount();
	}

	// Callback when player's health is updated
	void GameplayHUD::PlayerHealthUpdated(float changeAmt, float currentHealth, float maxHealth)
	{
		// LOG("Player Health Updated: %f, Current Health: %f/%f", changeAmt, currentHealth, maxHealth);
		m_PlayerHealthBar.UpdateValue(currentHealth, maxHealth);
		if (currentHealth / maxHealth <= m_HealthWarningThreshold &&
			currentHealth / maxHealth > m_HealthDangerThreshold)
		{
			m_PlayerHealthBar.SetForegroundColor(m_WarningHealthBarColor);
		}
		else if (currentHealth / maxHealth <= m_HealthDangerThreshold)
		{
			m_PlayerHealthBar.SetForegroundColor(m_DangerHealthBarColor);
		}
		else
		{
			m_PlayerHealthBar.SetForegroundColor(m_HealthyHealthBarColor);
		}
	}

	void GameplayHUD::PlayerLifeCountUpdated(int changeAmt)
	{
		m_PlayerLivesText.SetTextString(std::to_string(changeAmt));
	}

	void GameplayHUD::RefreshHealthBar()
	{
		Player* player = PlayerManager::Get().GetPlayer();
		// subscribe to player's spaceship health change event 
		// to update the health bar accordingly
		if (player && !player->GetCurrentPlayerSpaceship().expired())
		{
			weak<PlayerSpaceship> playerSpaceship = player->GetCurrentPlayerSpaceship();
			playerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameplayHUD::PlayerSpaceshipDestroyed);

			HealthComponent& healthComp = player->GetCurrentPlayerSpaceship().lock()->GetHealthComponent();
			healthComp.onHealthChanged.BindAction(GetWeakRef(), &GameplayHUD::PlayerHealthUpdated);
			// reset health bar color to healthy
			PlayerHealthUpdated(0.0f, healthComp.GetHealth(), healthComp.GetMaxHealth());
			m_PlayerHealthBar.UpdateValue(healthComp.GetHealth(), healthComp.GetMaxHealth());
		}
	}

	void GameplayHUD::ConnectPlayerLifeCount()
	{
		Player* player = PlayerManager::Get().GetPlayer();
		if (player)
		{
			int lifeCount = player->GetPlayerLifeCount();
			std::string lifeCountStr = std::to_string(lifeCount);
			m_PlayerLivesText.SetTextString(lifeCountStr);
			player->onLifeCountChanged.BindAction(GetWeakRef(), &GameplayHUD::PlayerLifeCountUpdated);
		}
	}

	void GameplayHUD::PlayerSpaceshipDestroyed(Actor* actor)
	{
		// when player's spaceship is destroyed, reset the health bar
		RefreshHealthBar();
	}
}
