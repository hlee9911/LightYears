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
		m_PlayerHealthBar{}
	{
		m_FrameRateText.SetTextSize(25);
	}

	void GameplayHUD::Draw(sf::RenderWindow& windowRef)
	{
		m_FrameRateText.NativeDraw(windowRef);
		m_PlayerHealthBar.NativeDraw(windowRef);
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
		
		RefreshHealthBar();
	}

	// Callback when player's health is updated
	void GameplayHUD::PlayerHealthUpdated(float changeAmt, float currentHealth, float maxHealth)
	{
		// LOG("Player Health Updated: %f, Current Health: %f/%f", changeAmt, currentHealth, maxHealth);
		m_PlayerHealthBar.UpdateValue(currentHealth, maxHealth);
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
			m_PlayerHealthBar.UpdateValue(healthComp.GetHealth(), healthComp.GetMaxHealth());
		}
	}

	void GameplayHUD::PlayerSpaceshipDestroyed(Actor* actor)
	{
		// when player's spaceship is destroyed, reset the health bar
		RefreshHealthBar();
	}
}
