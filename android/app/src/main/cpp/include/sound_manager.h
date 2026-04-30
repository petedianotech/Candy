#pragma once

#include <string>

class SoundManager {
public:
    SoundManager();
    ~SoundManager();

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