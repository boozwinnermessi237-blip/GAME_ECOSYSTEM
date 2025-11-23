#include "Graphics/Window.h"
#include <iostream>

namespace Ecosystem {
namespace Graphics {

// -------------------------------------------------------------
//  CONSTRUCTEUR
// -------------------------------------------------------------
Window::Window(const std::string& title, float width, float height)
    : mWindow(nullptr),
      mRenderer(nullptr),
      mWidth(width),
      mHeight(height),
      mIsInitialized(false),
      mTitle(title)
{
}

// -------------------------------------------------------------
//  DESTRUCTEUR
// -------------------------------------------------------------
Window::~Window()
{
    Shutdown();
}

// -------------------------------------------------------------
//  INITIALISATION SDL + FENÊTRE + RENDERER
// -------------------------------------------------------------
bool Window::Initialize()
{
    if (mIsInitialized)
        return true;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << " SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Création fenêtre
    mWindow = SDL_CreateWindow(
        mTitle.c_str(),
        static_cast<int>(mWidth),
        static_cast<int>(mHeight),
        SDL_WINDOW_RESIZABLE
    );

    if (!mWindow) {
        std::cerr << " SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Création renderer
    mRenderer = SDL_CreateRenderer(mWindow, nullptr);
    if (!mRenderer) {
        std::cerr << " SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
    }

    mIsInitialized = true;

    std::cout << "✅ Fenêtre SDL initialisée : " << mTitle
              << " (" << mWidth << "x" << mHeight << ")\n";

    return true;
}

// -------------------------------------------------------------
//  FERMETURE
// -------------------------------------------------------------
void Window::Shutdown()
{
    if (mRenderer) {
        SDL_DestroyRenderer(mRenderer);
        mRenderer = nullptr;
    }

    if (mWindow) {
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
    }

    SDL_Quit();

    mIsInitialized = false;
}

// -------------------------------------------------------------
//  EFFACER L'ÉCRAN
// -------------------------------------------------------------
void Window::Clear(const Core::Color& color)
{
    if (!mRenderer)
        return;

    SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, 255);
    SDL_RenderClear(mRenderer);
}

// -------------------------------------------------------------
//  AFFICHER LE RENDU
// -------------------------------------------------------------
void Window::Present()
{
    if (mRenderer)
        SDL_RenderPresent(mRenderer);
}

} // namespace Graphics
} // namespace Ecosystem
