<<<<<<< HEAD
#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "config.h"
#include <vector>
#include <memory>

class Particle {
public:
    Particle(Vector2 pos, Vector2 vel, Color col, float life);
    
    void update(float dt);
    void render();
    bool isAlive() const { return lifeTime > 0; }
    
private:
    Vector2 position;
    Vector2 velocity;
    Color color;
    float lifeTime;
    float maxLifeTime;
    float size;
=======
#pragma once

#include <vector>
#include "config.h"

struct Particle {
    Vector2A position;
    Vector2A velocity;
    ColorA color;
    float life;
    float maxLife;
>>>>>>> 23eafac (Add complete C++ Fruit Burst game with Android APK build setup)
};

class ParticleSystem {
public:
    ParticleSystem();
    ~ParticleSystem();
<<<<<<< HEAD
    
    void update(float dt);
    void render();
    
    // Emitters
    void emitExplosion(Vector2 position, Color color, int particleCount = 20);
    void emitMatch(Vector2 position, Color color);
    void emitPowerUp(Vector2 position);
    void emitCombo(Vector2 position, int comboCount);
    
private:
    std::vector<std::unique_ptr<Particle>> particles;
};

#endif // PARTICLE_SYSTEM_H
=======

    void update(float deltaTime);
    void render();

    void emitExplosion(int x, int y, ColorA color, int count = 10);
    void emitMatchEffect(int x, int y, ColorA color);
    void emitComboEffect(int x, int y, int comboLevel);

private:
    std::vector<Particle> particles;

    void addParticle(const Particle& particle);
};
>>>>>>> 23eafac (Add complete C++ Fruit Burst game with Android APK build setup)
