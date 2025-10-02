#ifndef CDURATION_HPP
#define CDURATION_HPP

#include <chrono>

using std::chrono::duration;
using std::chrono::high_resolution_clock;
using std::chrono::time_point;

struct CDuration
{
    CDuration(duration<double> timeAlive_) : m_birth(high_resolution_clock::now()), m_timeAlive(timeAlive_) {}

    duration<double> m_timeAlive;
    time_point<high_resolution_clock> m_birth;
};

#endif // CDURATION_HPP