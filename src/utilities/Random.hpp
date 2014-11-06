#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>

class Random {
public:
    static unsigned GENERATE() {
        return RNG();
    }

private:
    static std::random_device RNG;
};

#endif
