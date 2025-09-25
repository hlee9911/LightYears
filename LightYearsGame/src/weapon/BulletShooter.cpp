#include "weapon/BulletShooter.h"
#include "weapon/Bullet.h"
#include "framework/Core.h"
#include "framework/World.h"

namespace ly
{
	BulletShooter::BulletShooter(Actor* owner, float cooldownTime) noexcept
		: Shooter{ owner },
		m_CooldownClock{},
		m_CooldownTime{ cooldownTime }
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

	void BulletShooter::ShootImpl()
	{
		m_CooldownClock.restart();
		// LOG("Shooting!");
		weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
		newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardDirection() * 50.0f);
		newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation());
	}
}
