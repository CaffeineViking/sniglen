#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>

class Random {
public:
    static unsigned GENERATE();
    static int GENERATE_MAX(int);
    static int GENERATE_MINMAX(int, int);

private:
    static std::random_device RNG;
};

#endif
