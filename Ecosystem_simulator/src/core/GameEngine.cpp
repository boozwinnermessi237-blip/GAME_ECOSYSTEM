#include "Core/GameEngine.hpp"
#include <iostream>
#include <iomanip>
#include <SDL3/SDL.h>

namespace Ecosystem {
namespace Core {

// ---------------------------------------------------------
// Constructeur
// ---------------------------------------------------------
GameEngine::GameEngine(const std::string& title, float width, float height)
    : mWindow(title, width, height),
      mEcosystem(width, height, 300),
      mIsRunning(false),
      mIsPaused(false),
      mTimeScale(1.0f),
      mAccumulatedTime(0.0f)
{
}

// ---------------------------------------------------------
// Initialisation du moteur
// ---------------------------------------------------------
bool GameEngine::Initialize()
{
    std::cout << "\n=====================================\n";
    std::cout << "        SIMULATEUR D'ECOSYSTEME\n";
    std::cout << "=====================================\n";

    if (!mWindow.Initialize()) {
        std::cerr << "Erreur : impossible d'initialiser la fenêtre SDL.\n";
        return false;
    }

    // Initialisation de l'écosystème
    mEcosystem.Initialize(15, 3, 25);

    mIsRunning = true;
    mLastUpdateTime = std::chrono::high_resolution_clock::now();

    std::cout << "Commandes :\n";
    std::cout << " Espace : Pause / Reprise\n";
    std::cout << " R      : Réinitialiser\n";
    std::cout << " F      : Ajouter de la nourriture\n";
    std::cout << " H      : Ajouter un herbivore\n";
    std::cout << " C      : Ajouter un carnivore\n";
    std::cout << " P      : Ajouter une plante\n";
    std::cout << " Haut   : Accélérer\n";
    std::cout << " Bas    : Ralentir\n";
    std::cout << " Echapp : Quitter\n";

    return true;
}

// ---------------------------------------------------------
// Boucle principale
// ---------------------------------------------------------
void GameEngine::Run()
{
    while (mIsRunning) 
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsed = currentTime - mLastUpdateTime;
        mLastUpdateTime = currentTime;

        float deltaTime = elapsed.count();

        if (deltaTime > 0.1f)
            deltaTime = 0.1f;

        HandleEvents();

        if (!mIsPaused) {
            Update(deltaTime * mTimeScale);
        }

        Render();

        SDL_Delay(16); // ~60 FPS
    }
}

// ---------------------------------------------------------
// Extinction du moteur
// ---------------------------------------------------------
void GameEngine::Shutdown()
{
    mIsRunning = false;
    mWindow.Shutdown();
    std::cout << "Fermeture du moteur de jeu.\n";
}

// ---------------------------------------------------------
// Gestion des événements SDL
// ---------------------------------------------------------
void GameEngine::HandleEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) 
    {
        switch (event.type) 
        {
            case SDL_EVENT_QUIT:
                mIsRunning = false;
                break;

            case SDL_EVENT_KEY_DOWN:
                HandleInput(event.key.key);
                break;

            default:
                break;
        }
    }
}

// ---------------------------------------------------------
// Gestion des touches
// ---------------------------------------------------------
void GameEngine::HandleInput(SDL_Keycode key)
{
    switch (key)
    {
        case SDLK_ESCAPE:
            mIsRunning = false;
            break;

        case SDLK_SPACE:
            mIsPaused = !mIsPaused;
            break;

        case SDLK_R:
            mEcosystem.Initialize(15, 3, 25);
            break;

        case SDLK_F:
            mEcosystem.SpawnFood(20);
            break;

        case SDLK_H:
            mEcosystem.SpawnHerbivore();
            break;

        case SDLK_C:
            mEcosystem.SpawnCarnivore();
            break;

        case SDLK_P:
            mEcosystem.SpawnPlant();
            break;

        case SDLK_UP:
            mTimeScale *= 1.5f;
            if (mTimeScale > 10.0f) mTimeScale = 10.0f;
            break;

        case SDLK_DOWN:
            mTimeScale /= 1.5f;
            if (mTimeScale < 0.1f) mTimeScale = 0.1f;
            break;

        default:
            break;
    }
}

// ---------------------------------------------------------
// Mise à jour de l'écosystème
// ---------------------------------------------------------
void GameEngine::Update(float deltaTime)
{
    mEcosystem.Update(deltaTime);
}

// ---------------------------------------------------------
// Rendu graphique
// ---------------------------------------------------------
void GameEngine::Render()
{
    mWindow.Clear(Core::Color(20, 25, 30));

    mEcosystem.Render(mWindow.GetRenderer());

    RenderUI();

    mWindow.Present();
}

// ---------------------------------------------------------
// Interface utilisateur (console, basique)
// ---------------------------------------------------------
void GameEngine::RenderUI()
{
    // Future UI graphique via SDL_ttf ou ImGui
}

} // namespace Core
} // namespace Ecosystem
