#include "weapon/BulletShooter.h"
#include "weapon/Bullet.h"
#include "framework/Core.h"
#include "framework/World.h"

namespace ly
{
	BulletShooter::BulletShooter(Actor* owner, float cooldownTime, const sf::Vector2f& localPositionOffset, float localRotationOffset, const std::string& bulletTexturePath) noexcept
		: Shooter{ owner },
		m_CooldownClock{},
		m_CooldownTime{ cooldownTime },
		m_LocalPositionOffset{ localPositionOffset },
		m_LocalRotationOffset{ localRotationOffset },
		m_BulletTexturePath{ bulletTexturePath }
	{

	}

	bool BulletShooter::CanShoot() const
	{
		return true;
	}

	bool BulletShooter::IsOnCooldown() const
	{
		if (m_CooldownClock.getElapsedTime().asSeconds() >= m_CooldownTime)
		{
			return false;
		}
		return true;
	}

	void BulletShooter::SetBulletTexturePath(const std::string& bulletTexturePath) noexcept
	{
		m_BulletTexturePath = bulletTexturePath;
	}

	void BulletShooter::ShootImpl()
	{
		sf::Vector2f ownerForwardDir = GetOwner()->GetActorForwardDirection();
		sf::Vector2f ownerRightDir = GetOwner()->GetActorRightDirection();

		m_CooldownClock.restart();
		weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), m_BulletTexturePath);
		newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation() + ownerForwardDir * m_LocalPositionOffset.x + ownerRightDir * m_LocalPositionOffset.y);
		newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation() + m_LocalRotationOffset);
	}
}
