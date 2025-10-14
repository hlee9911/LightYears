#pragma once
#ifndef TIMERMANAGER_H
#define TIMERMANAGER_H

#include "framework/Core.h"
#include "framework/Object.h"

#include <functional>

namespace ly
{
	struct TimerHandle
	{
	public:
		TimerHandle() noexcept;
		unsigned int GetTimerKey() const noexcept { return m_TimerKey; }

	private:
		static unsigned int GetNextTimerKey() noexcept { return ++s_TimerKeyCounter; }

	private:
		static unsigned int s_TimerKeyCounter;
		unsigned int m_TimerKey;
	};

	struct TimerHandleHashFunction
	{
	public:
		std::size_t operator()(const TimerHandle& timerHandle) const
		{
			return timerHandle.GetTimerKey();
		}
	};

	// no need to put this inside the class 
	bool operator==(const TimerHandle& lhs, const TimerHandle& rhs);

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
	
		// interafce for the settimer
		template<typename ClassName>
		TimerHandle SetTimer(weak<Object> weakRef, void(ClassName::*callback)(), float duration, bool repeat = false)
		{
			TimerHandle newHandle{};
			m_Timers.insert({ newHandle, Timer(weakRef, [=] {(static_cast<ClassName*>(weakRef.lock().get())->*callback)(); }, duration, repeat) });
			return newHandle;
		}

		void UpdateTimer(float deltaTime);
		void ClearTimer(TimerHandle timerHandle);

	protected:
		TimerManager() noexcept;

	private:
		static unique<TimerManager> s_TimerManager;
		// static unsigned int s_TimerIndexCounter;

		// hash table doesnt know how to hash key with custom struct
		// so we need our custom hash function
		Dictionary<TimerHandle, Timer, TimerHandleHashFunction> m_Timers;
	};
}

#endif // TIMERMANAGER_H
