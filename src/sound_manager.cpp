#include "sound_manager.h"
<<<<<<< HEAD

SoundManager::SoundManager() {
}

SoundManager::~SoundManager() {
    if (initialized) {
        UnloadSound(matchSound);
        UnloadSound(swapSound);
        UnloadSound(powerUpSound);
        UnloadSound(comboSound);
        UnloadSound(levelCompleteSound);
        UnloadSound(buttonSound);
        UnloadMusicStream(backgroundMusic);
    }
}

void SoundManager::init() {
    // Note: In production, load actual sound files
    // For now, we'll use generated sounds
    
    // Create simple beep sounds programmatically
    // This is a fallback for demo purposes
    
    initialized = true;
}

void SoundManager::playMatchSound() {
    if (initialized && matchSound.frameCount > 0) {
        PlaySound(matchSound);
    }
}

void SoundManager::playSwapSound() {
    if (initialized && swapSound.frameCount > 0) {
        PlaySound(swapSound);
    }
}

void SoundManager::playPowerUpSound() {
    if (initialized && powerUpSound.frameCount > 0) {
        PlaySound(powerUpSound);
    }
}

void SoundManager::playComboSound() {
    if (initialized && comboSound.frameCount > 0) {
        PlaySound(comboSound);
    }
}

void SoundManager::playLevelCompleteSound() {
    if (initialized && levelCompleteSound.frameCount > 0) {
        PlaySound(levelCompleteSound);
    }
}

void SoundManager::playButtonSound() {
    if (initialized && buttonSound.frameCount > 0) {
        PlaySound(buttonSound);
    }
}

void SoundManager::stopMusic() {
    if (initialized && backgroundMusic.frameCount > 0) {
        StopMusicStream(backgroundMusic);
    }
}

void SoundManager::playBackgroundMusic() {
    if (initialized && backgroundMusic.frameCount > 0) {
        PlayMusicStream(backgroundMusic);
    }
}

void SoundManager::setMusicVolume(float volume) {
    if (initialized && backgroundMusic.frameCount > 0) {
        SetMusicVolume(backgroundMusic, volume);
    }
}

void SoundManager::setSoundVolume(float volume) {
    SetMasterVolume(volume);
}

Sound SoundManager::createSound(const std::string& filename) {
    // Would load sound from file in production
    return Sound{};
}
=======
#include "config.h"

SoundManager::SoundManager() : volume(1.0f) {
    loadSounds();
}

SoundManager::~SoundManager() {
    unloadSounds();
}

void SoundManager::playMatchSound() {
    LOGI("Playing match sound\n");
    // In a real implementation, play actual sound
}

void SoundManager::playSwapSound() {
    LOGI("Playing swap sound\n");
}

void SoundManager::playLevelCompleteSound() {
    LOGI("Playing level complete sound\n");
}

void SoundManager::playGameOverSound() {
    LOGI("Playing game over sound\n");
}

void SoundManager::playBackgroundMusic() {
    LOGI("Playing background music\n");
}

void SoundManager::setVolume(float vol) {
    volume = vol;
}

void SoundManager::loadSounds() {
    // Load sound files here
    LOGI("Loading sounds...\n");
}

void SoundManager::unloadSounds() {
    // Unload sound files here
    LOGI("Unloading sounds...\n");
}
>>>>>>> 23eafac (Add complete C++ Fruit Burst game with Android APK build setup)
