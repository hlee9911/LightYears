#pragma once

#include "enemy/EnemySpaceship.h"
#include "weapon/BulletShooter.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/FrontalWiper.h"

namespace ly
{
	class Boss : public EnemySpaceship
	{
	public:
		Boss(World* owningWorld, 
			const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/boss.png") noexcept;

		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;

	private:
		virtual void Shoot() override;
		
		void CheckMove();
		void ShootBaseShooters();
		void ShootThreeWayShooter();
		void ShootFrontalWipers();

		void HealthChanged(float amt, float currentHealth, float maxHealth);

		void SetStage(int newStage);

	private:
		float m_Speed;
		float m_BaseSpeed;
		float m_SwitchDistanceToEdge;

		unique<BulletShooter> m_BaseShooterLeft;
		unique<BulletShooter> m_BaseShooterRight;

		unique<ThreeWayShooter> m_ThreeWayShooter;

		unique<FrontalWiper> m_FrontalWiperLeft;
		unique<FrontalWiper> m_FrontalWiperRight;

		unique<BulletShooter> m_FinalStageShooterLeft;
		unique<BulletShooter> m_FinalStageShooterRight;

		int m_Stage;
	};
}
