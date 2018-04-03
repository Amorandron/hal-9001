
#include "timer.h"

void hal::Timer::start() {
    start_time = std::chrono::system_clock::now();
}

void hal::Timer::reset() {
    start();
}

std::chrono::milliseconds hal::Timer::elapsed() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_time);
}

int hal::Timer::elapsed_int() const {
    return elapsed().count();
}
