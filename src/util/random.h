
#ifndef HAL_9001_RANDOM_H
#define HAL_9001_RANDOM_H

#include <random>
#include <set>
#include <vector>

namespace hal {
    class Random {
    public:
        Random()
            : rng(rd()) {}

        template<typename T>
        T range(T min, T max) {
            std::uniform_int_distribution<T> dist(min, max);
            return dist(rng);
        }

        template<typename O>
        O random_set(std::set<O>& set) {
            std::vector<O> container;

            for(O element : set)
                container.push_back(element);

            return container[range<size_t>(0, container.size() - 1)];
        }

    private:
        std::random_device rd;
        std::mt19937 rng;
    };
}

#endif
