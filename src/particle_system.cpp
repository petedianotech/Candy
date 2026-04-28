#include "particle_system.h"
#include <cmath>
#include <cstdlib>
#include <algorithm>

Particle::Particle(Vector2 pos, Vector2 vel, Color col, float life)
    : position(pos), velocity(vel), color(col), lifeTime(life), 
      maxLifeTime(life), size(4.0f) {
}

void Particle::update(float dt) {
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
    
    // Apply gravity
    velocity.y += 200.0f * dt;
    
    // Fade out
    lifeTime -= dt;
    color.a = (uint8_t)(255 * (lifeTime / maxLifeTime));
}

void Particle::render() {
    if (lifeTime <= 0) return;
    
    float alpha = lifeTime / maxLifeTime;
    Color drawColor = color;
    drawColor.a = (uint8_t)(255 * alpha);
    
    DrawCircle((int)position.x, (int)position.y, size * alpha, drawColor);
}

ParticleSystem::ParticleSystem() {
}

ParticleSystem::~ParticleSystem() {
}

void ParticleSystem::update(float dt) {
    for (auto& particle : particles) {
        particle->update(dt);
    }
    
    // Clean up dead particles
    particles.erase(
        std::remove_if(particles.begin(), particles.end(),
            [](const std::unique_ptr<Particle>& p) { return !p->isAlive(); }),
        particles.end()
    );
}

void ParticleSystem::render() {
    for (auto& particle : particles) {
        particle->render();
    }
}

void ParticleSystem::emitExplosion(Vector2 position, Color color, int particleCount) {
    for (int i = 0; i < particleCount; ++i) {
        float angle = (2 * 3.14159f * i) / particleCount;
        float speed = 100.0f + (rand() % 100);
        
        Vector2 vel = {
            std::cos(angle) * speed,
            std::sin(angle) * speed
        };
        
        particles.push_back(std::make_unique<Particle>(position, vel, color, 1.0f));
    }
}

void ParticleSystem::emitMatch(Vector2 position, Color color) {
    emitExplosion(position, color, 12);
}

void ParticleSystem::emitPowerUp(Vector2 position) {
    Color colors[] = {YELLOW, GOLD, LIME, BLUE};
    for (int i = 0; i < 4; ++i) {
        float angle = (2 * 3.14159f * i) / 4;
        Vector2 vel = {
            std::cos(angle) * 150.0f,
            std::sin(angle) * 150.0f
        };
        
        particles.push_back(std::make_unique<Particle>(position, vel, colors[i], 0.8f));
    }
}

void ParticleSystem::emitCombo(Vector2 position, int comboCount) {
    Color comboColor = ORANGE;
    
    float angle = 0;
    for (int i = 0; i < 8; ++i) {
        angle = (2 * 3.14159f * i) / 8;
        Vector2 vel = {
            std::cos(angle) * 200.0f,
            std::sin(angle) * 200.0f
        };
        
        particles.push_back(std::make_unique<Particle>(position, vel, comboColor, 1.0f));
    }
}
