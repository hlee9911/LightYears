#pragma once
#ifndef TIMERMANAGER_H
#define TIMERMANAGER_H

#include "framework/Core.h"
#include "framework/Object.h"

namespace ly
{
	class TimerManager
	{
	public:
		static TimerManager& Get();
	
		// interfce for the settimer
		template<typename ClassName>
		void SetTimer(weak<Object> weakRef, void(ClassName::*callback)(), float duration, bool repeat = false)
		{

		}

	protected:
		TimerManager() noexcept;

	private:
		static unique<TimerManager> s_TimerManager;
	};
}

#endif // TIMERMANAGER_H
