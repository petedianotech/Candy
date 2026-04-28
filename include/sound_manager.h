#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include "config.h"
#include <memory>
#include <string>

class SoundManager {
public:
    SoundManager();
    ~SoundManager();
    
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
