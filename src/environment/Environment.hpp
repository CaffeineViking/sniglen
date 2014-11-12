#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

class Environment {
public:
    Environment() = default;
    Environment(float gravity) : gravity_{gravity} {}
    void randomizeWind();
    float getWindForce() const;

private:
    float windForce_{0.0f};
    const float gravity_{9.8f};
};

#endif
