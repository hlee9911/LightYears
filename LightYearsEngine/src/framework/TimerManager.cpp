#include "framework/TimerManager.h"

namespace ly
{
    /////////////////////////// Timer part /////////////////////////

    Timer::Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat) noexcept
        : m_Listener{ weakRef, callback },
        m_Duration{ duration },
        m_Repeat{ repeat },
        m_TimeCounter{ 0.0f },
        m_IsExpired{ false }
    {

    }

    void Timer::TickTime(float deltaTime)
    {
        if (Expired()) return;

        m_TimeCounter += deltaTime;

        // after the certain amount of duration has passed, 
        if (m_TimeCounter >= m_Duration)
        {
            m_Listener.second(); // invoke the callback function stored in m_Listener

            if (m_Repeat)
            {
                m_TimeCounter = 0.0f;
            }
            else
            {
                SetExpired();
            }
        }
    }

    bool Timer::Expired() const noexcept
    {
        return m_IsExpired || m_Listener.first.expired() || m_Listener.first.lock()->IsPendingDestroy();
    }

    void Timer::SetExpired() noexcept
    {
        m_IsExpired = true;
    }

    /////////////////////// TimerManager part ////////////////////////

    unique<TimerManager> TimerManager::s_TimerManager{ nullptr };
    unsigned int TimerManager::s_TimerIndexCounter{ 0 };

    TimerManager& TimerManager::Get()
    {
        if (!s_TimerManager)
        {
            s_TimerManager = std::move(unique<TimerManager>(new TimerManager{}));
        }
        return *s_TimerManager;
    }

    void TimerManager::UpdateTimer(float deltaTime)
    {
        for (auto iter = m_Timers.begin(); iter != m_Timers.end();)
        {
            if (iter->second.Expired())
            {
                iter = m_Timers.erase(iter);
            }
            else
            {
                iter->second.TickTime(deltaTime);
                ++iter;
            }
        }
    }

    void TimerManager::ClearTimer(unsigned int timerIndex)
    {
        auto iter = m_Timers.find(timerIndex);
        if (iter != m_Timers.end())
        {
            iter->second.SetExpired();
        }
    }

    TimerManager::TimerManager() noexcept
        : m_Timers{}
    {

    }
}
