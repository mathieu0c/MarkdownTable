#ifndef PERFTOOLS_SCOPETIMER_H
#define PERFTOOLS_SCOPETIMER_H

#include <chrono>
#include <string>
#include <vector>

namespace perfTools {

bool useless();

class ScopeTimer
{
private:
    using TimeP_t = std::chrono::time_point<std::chrono::high_resolution_clock>;
    struct Duration
    {
        double val{};
        std::string unit{};
    };
    

public:
    ScopeTimer(std::string context = "context");

    void step();

    ~ScopeTimer();

private:
    inline
    Duration getDuration(TimeP_t start,TimeP_t end);

private:
    TimeP_t m_startPoint;
    std::vector<TimeP_t> m_steps;
    std::string m_context;
    int m_stepCount;
};

inline
ScopeTimer::Duration ScopeTimer::getDuration(TimeP_t start,TimeP_t end)
{
    auto duration{(double)(std::chrono::duration_cast<std::chrono::microseconds>(end-start).count())};
    if(duration > 1000)
    {
        return {duration/1000.,"ms"};
    }
    return {duration,"µs"};
}

} // namespace perfTools

#endif // PERFTOOLS_SCOPETIMER_H
