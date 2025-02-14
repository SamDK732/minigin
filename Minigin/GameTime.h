#ifndef TIME
#define TIME

#include "Singleton.h"

#include <chrono>


class GameTime final : public dae::Singleton<GameTime>
{
public:
    [[nodiscard]] float GetElapsedSec() const { return m_ElapsedSec; }
    [[nodiscard]] float GetFixedTimeStep() const { return m_FixedTimeStep; }

    [[nodiscard]] bool IsLag() const { return m_Lag >= m_FixedTimeStep; }

    void ProcessLag() { m_Lag -= m_FixedTimeStep; }

    void Update();

    [[nodiscard]] auto GetSleepTime() const
    {
        const auto sleepTime{ m_LastTime + std::chrono::milliseconds(static_cast<long>(m_MsPerFrame)) - std::chrono::high_resolution_clock::now() };
        return sleepTime;
    }

    GameTime(const GameTime&) = delete;
    GameTime(GameTime&&) = delete;
    GameTime& operator=(const GameTime&) = delete;
    GameTime& operator=(const GameTime&&) = delete;

private:
    friend class dae::Singleton<GameTime>;
    GameTime() = default;
    ~GameTime() = default;

    std::chrono::steady_clock::time_point m_LastTime{ std::chrono::high_resolution_clock::now() };

    const float m_MsPerFrame{ 16.7f };
    const float m_FixedTimeStep{ 20.f };

    float m_ElapsedSec{ 0.f };
    float m_Lag{ 0.f };
};

#endif

