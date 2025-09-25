#pragma once
#ifndef SHOOTER_H
#define SHOOTER_H

namespace ly
{
	class Actor;
	class Shooter
	{
	public:
		void Shoot();

		virtual bool CanShoot() const { return true; }
		virtual bool IsOnCooldown() const { return false; }

		Actor* GetOwner() const noexcept { return m_Owner; }

	protected:
		Shooter(Actor* owner) noexcept;

	private:
		virtual void ShootImpl() = 0;

	private:
		Actor* m_Owner;
	};
}

#endif // SHOOTER_H
