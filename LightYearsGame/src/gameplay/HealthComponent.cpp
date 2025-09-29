#include "gameplay/HealthComponent.h"
#include "framework/Core.h"

namespace ly
{
	HealthComponent::HealthComponent(float currentHealth, float maxHealth) noexcept
		: m_CurrentHealth{ currentHealth },
		m_MaxHealth{ maxHealth }
	{

	}

	void HealthComponent::ChangeHealth(float amt)
	{
		if (amt == 0.0f || m_CurrentHealth == 0.0f) return;

		m_CurrentHealth += amt;
		if (m_CurrentHealth > m_MaxHealth)
		{
			m_CurrentHealth = m_MaxHealth;
		}

		if (m_CurrentHealth < 0.0f)
		{
			m_CurrentHealth = 0.0f;
		}

		if (amt < 0.0f)
		{
			TakenDamange(-amt);
			if (m_CurrentHealth <= 0.0f)
			{
				HealthEmpty();
			}
		}

		onHealthChanged.Broadcast(amt, m_CurrentHealth, m_MaxHealth);
	}

	void HealthComponent::TakenDamange(float amt)
	{
		// LOG("Took Damage: %f, Current Health: %f/%f", amt, m_CurrentHealth, m_MaxHealth);
		onTakenDamage.Broadcast(amt, m_CurrentHealth, m_MaxHealth);
	}

	void HealthComponent::HealthEmpty()
	{
		// LOG("You Died");
		onHealthEmpty.Broadcast();
	}

}
