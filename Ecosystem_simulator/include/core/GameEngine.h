#pragma once

#include "../Graphics/Window.hpp"
#include "Ecosystem.hpp"
#include <chrono>

namespace Ecosystem {
namespace Core {

class GameEngine {
private:
    // État interne du moteur
    Graphics::Window mWindow;
    Ecosystem mEcosystem;
    bool mIsRunning;
    bool mIsPaused;
    float mTimeScale;

    // Chronomètre
    std::chrono::high_resolution_clock::time_point mLastUpdateTime;
    float mAccumulatedTime;

public:
    // Constructeur
    GameEngine(const std::string& title, float width, float height);

    // Méthodes principales
    bool Initialize();
    void Run();
    void Shutdown();

    // Gestion des événements
    void HandleEvents();
    void HandleInput(SDL_Keycode key);

private:
    // Méthodes internes
    void Update(float deltaTime);
    void Render();
    void RenderUI();
};

} // namespace Core
} // namespace Ecosystem
