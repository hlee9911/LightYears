#pragma once
#ifndef TIMERMANAGER_H
#define TIMERMANAGER_H

#include "framework/Core.h"
#include "framework/Object.h"

#include <functional>

namespace ly
{
	struct Timer
	{
	public:
		Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat) noexcept;
		void TickTime(float deltaTime);
		bool Expired() const noexcept;
		void SetExpired() noexcept;

	private:
		std::pair<weak<Object>, std::function<void()>> m_Listener;
		float m_Duration;
		bool m_Repeat;
		float m_TimeCounter;
		bool m_IsExpired;
	};
	
	class TimerManager
	{
	public:
		static TimerManager& Get();
	
		// interfce for the settimer
		template<typename ClassName>
		void SetTimer(weak<Object> weakRef, void(ClassName::*callback)(), float duration, bool repeat = false)
		{
			m_Timers.push_back(Timer(weakRef, [=] {(static_cast<ClassName*>(weakRef.lock().get())->*callback)(); }, duration, repeat));
		}

		void UpdateTimer(float deltaTime);

	protected:
		TimerManager() noexcept;

	private:
		static unique<TimerManager> s_TimerManager;
		List<Timer> m_Timers;
	};
}

#endif // TIMERMANAGER_H
