#include "ScopeTimer.h"

#include "Utils.h"

#include <chrono>
#include <numeric>
#include <iomanip>


namespace perfTools {

ScopeTimer::ScopeTimer(std::string context) : m_startPoint{},
    m_steps(),
    m_context{std::move(context)},
    m_stepCount{}
{
    m_steps.reserve(2000);
    m_startPoint = std::chrono::high_resolution_clock::now();
}

void ScopeTimer::step()
{
    auto now{std::chrono::high_resolution_clock::now()};
    // auto duration{std::chrono::duration_cast<std::chrono::microseconds>(now-m_startPoint)};
    // double durationMs{(double)duration.count()/1000.};
    // m_stepCount++;
    // if(name.empty())
        // name = std::to_string(m_stepCount);

    // perfTools::getOutStream() << m_context << " : Step <"<<name<<">: \n" ;
    // perfTools::getOutStream() << "   From step :" << (double)(std::chrono::duration_cast<std::chrono::microseconds>(now-m_stepPoint).count()) << " ms\n";
    // perfTools::getOutStream() << "   From start :" << durationMs << " µs\n";
    // m_stepPoint = std::chrono::high_resolution_clock::now();
    m_steps.emplace_back(std::move(now));
}

ScopeTimer::~ScopeTimer()
{
    auto now{std::chrono::high_resolution_clock::now()};
    auto lambdaDisplay{
        [this]() -> auto&
        {
            return perfTools::getOutStream() << "~PerfTools~  " << this->m_context << "  ~~ ";
        }
    };

    lambdaDisplay() << "\n";
    for(int i{}; i < size(m_steps);++i)
    {
        auto timeStamp{getDuration(m_startPoint,m_steps[i])};
        lambdaDisplay()<<i<<" : "<<timeStamp.val<<" "<<timeStamp.unit;
        if(i > 0)
        {
            auto ts{getDuration(m_steps[i-1],m_steps[i])};
            perfTools::getOutStream() << "  -  " << ts.val<<" "<<ts.unit<<"\n";
        }
        else
        {
            perfTools::getOutStream() << "\n";
        }
    }
    auto timeStamp{getDuration(m_startPoint,now)};
    lambdaDisplay()<<"   From start :" << timeStamp.val<<" "<<timeStamp.unit<<"\n";
}

} // namespace perfTools
