#include "particle_system.h"
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