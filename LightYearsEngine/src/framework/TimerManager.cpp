#include "framework/TimerManager.h"

namespace ly
{
    unique<TimerManager> TimerManager::s_TimerManager{ nullptr };

    TimerManager::TimerManager() noexcept
    {

    }

    TimerManager& TimerManager::Get()
    {
        if (!s_TimerManager)
        {
            s_TimerManager = std::move(unique<TimerManager>(new TimerManager{}));
        }
        return *s_TimerManager;
    }
}
