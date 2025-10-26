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

		int GetCurrentLevel() const noexcept { return m_CurrentLevel; }
		int GetMaxLevel() const noexcept { return m_MaxLevel; }

		virtual void IncrementLevel(int amt = 1);
		virtual void SetCurrentLevel(int level) noexcept;

	protected:
		Shooter(Actor* owner) noexcept;

	private:
		virtual void ShootImpl() = 0;

	private:
		Actor* m_Owner;

		int m_CurrentLevel;
		int m_MaxLevel;
	};
}

#endif // SHOOTER_H
