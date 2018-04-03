
#ifndef HAL_9001_TIMER_H
#define HAL_9001_TIMER_H

#include <chrono>

namespace hal {
    class Timer {
    public:
        void start();
        void reset();
        std::chrono::milliseconds elapsed() const;
        int elapsed_int() const;


    private:
        std::chrono::system_clock::time_point start_time;
    };
}

#endif
