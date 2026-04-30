#pragma once

#include <vector>
#include "config.h"

struct Particle {
    Vector2A position;
    Vector2A velocity;
    ColorA color;
    float life;
    float maxLife;
};

class ParticleSystem {
public:
    ParticleSystem();
    ~ParticleSystem();

    void update(float deltaTime);
    void render();

    void emitExplosion(int x, int y, ColorA color, int count = 10);
    void emitMatchEffect(int x, int y, ColorA color);
    void emitComboEffect(int x, int y, int comboLevel);

private:
    std::vector<Particle> particles;

    void addParticle(const Particle& particle);
};