#include "enemy/Boss.h"
#include "gameplay/HealthComponent.h"

namespace ly
{
	Boss::Boss(World* owningWorld, const std::string& texturePath) noexcept
		: EnemySpaceship{ owningWorld, texturePath },
		m_Speed{ 150.0f },
		m_BaseSpeed{ 150.0f },
		m_SwitchDistanceToEdge{ 100.0f },
		m_BaseShooterLeft{ new BulletShooter{ this, 1.0f, sf::Vector2f{50.0f, -50.0f}, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		m_BaseShooterRight{ new BulletShooter{this, 1.0f, sf::Vector2f{50.0f, 50.0f}, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		m_ThreeWayShooter{ new ThreeWayShooter{ this, 4.0f, sf::Vector2f{100.0f, 0.0f}} },
		m_FrontalWiperLeft{ new FrontalWiper{ this, 5.0f, sf::Vector2f{80.0f, -100.0f}} },
		m_FrontalWiperRight{ new FrontalWiper{this, 5.0f, sf::Vector2f{80.0f, 100.0f}} },
		m_FinalStageShooterLeft{ new BulletShooter{ this, 0.3f, sf::Vector2f{25.0f, -150.0f}, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		m_FinalStageShooterRight{ new BulletShooter{ this, 0.3f, sf::Vector2f{25.0f, 150.0f}, 0.0f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"} },
		m_Stage{ 1 }
	{
		SetActorRotation(180.0f);
		SetVelocity(sf::Vector2f{ m_Speed, 0.0f });
		SetRewardSpawnWeight(0.0f); // Boss does not drop any reward
	}

	void Boss::BeginPlay()
	{
		EnemySpaceship::BeginPlay();

		HealthComponent& healthComp = GetHealthComponent();
		healthComp.SetInitialHealth(3000.0f, 3000.0f);
		healthComp.onHealthChanged.BindAction(GetWeakRef(), &Boss::HealthChanged);
		// SetStage(4);
	}

	void Boss::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);

		Shoot();
		CheckMove();
	}

	void Boss::Shoot()
	{
		ShootBaseShooters();
		ShootThreeWayShooter();
		ShootFrontalWipers();
	}

	void Boss::CheckMove()
	{
		if (GetActorLocation().x > GetWindowSize().x - m_SwitchDistanceToEdge)
		{
			SetVelocity(sf::Vector2f{ -m_Speed, 0.0f });
		}
		else if (GetActorLocation().x < m_SwitchDistanceToEdge)
		{
			SetVelocity(sf::Vector2f{ m_Speed, 0.0f });
		}
	}

	void Boss::ShootBaseShooters()
	{
		m_BaseShooterLeft->Shoot();
		m_BaseShooterRight->Shoot();

		if (m_Stage == 4)
		{
			m_FinalStageShooterLeft->Shoot();
			m_FinalStageShooterRight->Shoot();
		}
	}

	void Boss::ShootThreeWayShooter()
	{
		m_ThreeWayShooter->Shoot();
	}

	void Boss::ShootFrontalWipers()
	{
		m_FrontalWiperLeft->Shoot();
		m_FrontalWiperRight->Shoot();
	}

	void Boss::HealthChanged(float amt, float currentHealth, float maxHealth)
	{
		float healthPercentLeft = currentHealth / maxHealth;
		if (healthPercentLeft < 0.75f && healthPercentLeft > 0.5f)
		{
			SetStage(2);
		}
		else if (healthPercentLeft <= 0.5f && healthPercentLeft > 0.25f)
		{
			SetStage(3);
		}
		else if (healthPercentLeft <= 0.25f)
		{
			SetStage(4);
		}
	}

	void Boss::SetStage(int newStage)
	{
		m_Stage = newStage;

		m_BaseShooterLeft->SetCurrentLevel(m_Stage);
		m_BaseShooterRight->SetCurrentLevel(m_Stage);

		m_ThreeWayShooter->SetCurrentLevel(m_Stage);

		m_FrontalWiperLeft->SetCurrentLevel(m_Stage);
		m_FrontalWiperRight->SetCurrentLevel(m_Stage);

		m_Speed = m_Stage * m_BaseSpeed;
	}

}
