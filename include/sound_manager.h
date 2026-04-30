<<<<<<< HEAD
#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include "config.h"
#include <memory>
=======
#pragma once

>>>>>>> 23eafac (Add complete C++ Fruit Burst game with Android APK build setup)
#include <string>

class SoundManager {
public:
    SoundManager();
    ~SoundManager();
<<<<<<< HEAD
    
    void init();
    void playMatchSound();
    void playSwapSound();
    void playPowerUpSound();
    void playComboSound();
    void playLevelCompleteSound();
    void playButtonSound();
    void stopMusic();
    void playBackgroundMusic();
    
    void setMusicVolume(float volume);
    void setSoundVolume(float volume);
    
private:
    Sound matchSound;
    Sound swapSound;
    Sound powerUpSound;
    Sound comboSound;
    Sound levelCompleteSound;
    Sound buttonSound;
    
    Music backgroundMusic;
    
    bool initialized = false;
    
    Sound createSound(const std::string& filename);
};

#endif // SOUND_MANAGER_H
=======

    void playMatchSound();
    void playSwapSound();
    void playLevelCompleteSound();
    void playGameOverSound();
    void playBackgroundMusic();

    void setVolume(float volume);
    float getVolume() const { return volume; }

private:
    float volume;

    // In a real implementation, these would load actual sound files
    void loadSounds();
    void unloadSounds();
};
>>>>>>> 23eafac (Add complete C++ Fruit Burst game with Android APK build setup)
