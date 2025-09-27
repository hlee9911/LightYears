#pragma once
#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include "framework/Delegate.h"

namespace ly
{
	class HealthComponent
	{
	public:
		HealthComponent(float currentHealth, float maxHealth) noexcept;
		void ChangeHealth(float amt);
		float GetHealth() const noexcept { return m_CurrentHealth; }
		float GetMaxHealth() const noexcept { return m_MaxHealth; }

		Delegate<float, float, float> onHealthChanged;

	private:
		void TakenDamange(float amt);
		void HealthEmpty();
		void HealthRegen(float amt);

	private:
		float m_CurrentHealth;
		float m_MaxHealth;
	};
}

#endif // HEALTHCOMPONENT_H
