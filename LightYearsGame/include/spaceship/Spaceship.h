#pragma once
#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <string>

#include "framework/Actor.h"
#include "gameplay/HealthComponent.h"

namespace ly
{
	class Spaceship : public Actor
	{
	public:
		Spaceship(World* owningWorld, const std::string& texturePath = "") noexcept;
		virtual void Tick(float deltaTime) override;

		void SetVelocity(const sf::Vector2f& newVel) noexcept;
		sf::Vector2f GetVelocity() const noexcept { return m_Velocity; }

		virtual void Shoot();

		virtual void BeginPlay() override;

		virtual void ApplyDamage(float damageAmt) override;

	private:
		void Blink();
		void UpdateBlink(float deltaTime);

		virtual void OnHealthChanged(float amt, float health, float maxHealth);
		virtual void OnTakenDamage(float amt, float health, float maxHealth);
		virtual void OnBlow();

	private:
		sf::Vector2f m_Velocity;
		HealthComponent m_HealthComp;

		float m_BlinkTime;
		float m_BlinkDuration;
		sf::Color m_BlinkColorOffset;
	};
}

#endif // SPACESHIP_H
