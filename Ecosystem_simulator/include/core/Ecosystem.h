#pragma once
#include "Entity.h"
#include "Structs.h"
#include <vector>
#include <memory>
#include <random>
#include <SDL3/SDL.h>

namespace Ecosystem {
namespace Core {

class Ecosystem {
private:
    // État interne
    std::vector<std::unique_ptr<Entity>> mEntities;
    std::vector<Food> mFoodSources;
    float mWorldWidth;
    float mWorldHeight;
    int mMaxEntities;
    int mDayCycle;

    // Générateur aléatoire
    std::mt19937 mRandomGenerator;

    // Statistiques
    struct Statistics {
        int totalHerbivores;
        int totalCarnivores;
        int totalPlants;
        int totalFood;
        int deathsToday;
        int birthsToday;
    } mStats;

public:
    // Constructeur / Destructeur
    Ecosystem(float width, float height, int maxEntities = 500);
    ~Ecosystem();

    // Méthodes publiques
    void Initialize(int initialHerbivores, int initialCarnivores, int initialPlants);
    void Update(float deltaTime);
    void SpawnFood(int count);
    void RemoveDeadEntities();
    void HandleReproduction();
    void HandleEating();

    // Getters
    int GetEntityCount() const { return static_cast<int>(mEntities.size()); }
    int GetFoodCount() const { return static_cast<int>(mFoodSources.size()); }
    Statistics GetStatistics() const { return mStats; }
    float GetWorldWidth() const { return mWorldWidth; }
    float GetWorldHeight() const { return mWorldHeight; }

    // Rendu
    void Render(SDL_Renderer* renderer) const;

private:
    // Méthodes privées
    void UpdateStatistics();
    void SpawnRandomEntity(EntityType type);
    Vector2D GetRandomPosition() const;
    void HandlePlantGrowth(float deltaTime);
};

} // namespace Core
} // namespace Ecosystem
