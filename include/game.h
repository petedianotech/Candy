#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "input_handler.h"
#include "particle_system.h"
#include "ui.h"
#include "sound_manager.h"
#include <vector>
#include <memory>

class Game {
public:
    Game();
    ~Game();
    
    void init();
    void update(float dt);
    void render();
    bool isRunning() const;
    
private:
    enum class GameState {
        Playing,
        LevelComplete,
        GameOver,
        Menu,
        Paused
    };
    
    GameState state;
    std::unique_ptr<Board> board;
    std::unique_ptr<InputHandler> inputHandler;
    std::unique_ptr<ParticleSystem> particleSystem;
    std::unique_ptr<UI> ui;
    std::unique_ptr<SoundManager> soundManager;
    
    int currentLevel;
    int score;
    int targetScore;
    int moves;
    float levelTime;
    bool running;
    
    void handleInput(float dt);
    void updateGame(float dt);
    void renderGame();
    void checkLevelComplete();
    void nextLevel();
    void resetLevel();
};

#endif // GAME_H
