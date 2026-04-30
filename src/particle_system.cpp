#include "particle_system.h"
<<<<<<< HEAD
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
=======
#include "config.h"
#include <cstdlib>

ParticleSystem::ParticleSystem() = default;

ParticleSystem::~ParticleSystem() = default;

void ParticleSystem::update(float deltaTime) {
    for (auto it = particles.begin(); it != particles.end(); ) {
        it->life -= deltaTime;
        it->position.x += it->velocity.x * deltaTime;
        it->position.y += it->velocity.y * deltaTime;

        if (it->life <= 0) {
            it = particles.erase(it);
        } else {
            ++it;
        }
    }
}

void ParticleSystem::render() {
    for (const auto& particle : particles) {
        float alpha = particle.life / particle.maxLife;
        ColorA color = particle.color;
        color.a = static_cast<unsigned char>(alpha * 255);

        DrawCircleA(static_cast<int>(particle.position.x), static_cast<int>(particle.position.y),
                   3.0f, color);
    }
}

void ParticleSystem::emitExplosion(int x, int y, ColorA color, int count) {
    for (int i = 0; i < count; ++i) {
        Particle p;
        p.position = {static_cast<float>(x), static_cast<float>(y)};
        p.velocity = {static_cast<float>(rand() % 200 - 100), static_cast<float>(rand() % 200 - 100)};
        p.color = color;
        p.life = p.maxLife = 1.0f + (rand() % 100) / 100.0f;

        addParticle(p);
    }
}

void ParticleSystem::emitMatchEffect(int x, int y, ColorA color) {
    emitExplosion(x, y, color, 5);
}

void ParticleSystem::emitComboEffect(int x, int y, int comboLevel) {
    ColorA color = COLOR_YELLOW;
    if (comboLevel >= 3) color = COLOR_ORANGE;
    if (comboLevel >= 5) color = COLOR_RED;

    emitExplosion(x, y, color, 10 + comboLevel * 5);
}

void ParticleSystem::addParticle(const Particle& particle) {
    particles.push_back(particle);
}
>>>>>>> 23eafac (Add complete C++ Fruit Burst game with Android APK build setup)
