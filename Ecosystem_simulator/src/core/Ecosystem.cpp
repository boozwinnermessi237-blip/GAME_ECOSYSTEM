// Ecosystem.cpp 
#include "Ecosystem.h"
#include <iostream>
#include <random>

using namespace Ecosystem::Core;

// Constructeur / Destructeur

Ecosystem::Ecosystem(float width, float height, int maxEntities)
    : mWorldWidth(width),
      mWorldHeight(height),
      mMaxEntities(maxEntities),
      mDayCycle(0)
{
    std::random_device rd;
    mRandomGenerator.seed(rd());

    // Initialisation statistiques
    mStats = {0, 0, 0, 0, 0, 0};
}

Ecosystem::~Ecosystem() {
    mEntities.clear();
    mFoodSources.clear();
}

// Initialisation

void Ecosystem::Initialize(int initialHerbivores, int initialCarnivores, int initialPlants) {
    for(int i = 0; i < initialHerbivores; ++i)
        SpawnRandomEntity(EntityType::HERBIVORE);

    for(int i = 0; i < initialCarnivores; ++i)
        SpawnRandomEntity(EntityType::CARNIVORE);

    for(int i = 0; i < initialPlants; ++i)
        SpawnRandomEntity(EntityType::PLANT);

    UpdateStatistics();
}

// Mise à jour de l'écosystème

void Ecosystem::Update(float deltaTime) {
    for(auto& entity : mEntities) {
        if(entity->IsAlive())
            entity->Update(deltaTime, mWorldWidth, mWorldHeight);
    }

    HandleEating();
    HandleReproduction();
    HandlePlantGrowth(deltaTime);
    RemoveDeadEntities();
    UpdateStatistics();

    ++mDayCycle;
}

// Gestion de la nourriture

void Ecosystem::SpawnFood(int count) {
    for(int i = 0; i < count; ++i) {
        Food f;
        f.position = GetRandomPosition();
        f.energy = 20.0f;
        mFoodSources.push_back(f);
    }
}

// Suppression des entités mortes

void Ecosystem::RemoveDeadEntities() {
    mEntities.erase(
        std::remove_if(mEntities.begin(), mEntities.end(),
                       [](const std::unique_ptr<Entity>& e){ return !e->IsAlive(); }),
        mEntities.end()
    );
}

// Reproduction

void Ecosystem::HandleReproduction() {
    std::vector<std::unique_ptr<Entity>> newborns;

    for(auto& entity : mEntities) {
        if(entity->CanReproduce()) {
            auto child = entity->Reproduce();
            if(child)
                newborns.push_back(std::move(child));
        }
    }

    for(auto& baby : newborns)
        mEntities.push_back(std::move(baby));
}

// Gestion de la nourriture et énergie

void Ecosystem::HandleEating() {
    for(auto& entity : mEntities) {
        if(!entity->IsAlive()) continue;

        for(auto it = mFoodSources.begin(); it != mFoodSources.end(); ++it) {
            float dx = entity->position.x - it->position.x;
            float dy = entity->position.y - it->position.y;
            float dist2 = dx*dx + dy*dy;

            if(dist2 < (entity->size + 5.0f)*(entity->size + 5.0f)) {
                entity->Eat(it->energy);
                mFoodSources.erase(it);
                break;
            }
        }
    }
}

// Affichage / rendu


void Ecosystem::Render(SDL_Renderer* renderer) const {
    for(const auto& entity : mEntities)
        entity->Render(renderer);

    // Affichage nourriture
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    for(const auto& f : mFoodSources) {
        SDL_FRect rect = { f.position.x - 3, f.position.y - 3, 6, 6 };
        SDL_RenderFillRect(renderer, &rect);
    }
}

// Méthodes privées


void Ecosystem::UpdateStatistics() {
    mStats = {0, 0, 0, static_cast<int>(mFoodSources.size()), 0, 0};

    for(const auto& entity : mEntities) {
        if(!entity->IsAlive()) continue;

        switch(entity->GetType()) {
            case EntityType::HERBIVORE: ++mStats.totalHerbivores; break;
            case EntityType::CARNIVORE: ++mStats.totalCarnivores; break;
            case EntityType::PLANT:     ++mStats.totalPlants; break;
        }
    }
}

void Ecosystem::SpawnRandomEntity(EntityType type) {
    if(static_cast<int>(mEntities.size()) >= mMaxEntities) return;

    Vector2D pos = GetRandomPosition();
    std::string name = "Entity_" + std::to_string(mEntities.size());
    mEntities.push_back(std::make_unique<Entity>(type, pos, name));
}

Vector2D Ecosystem::GetRandomPosition() const {
    std::uniform_real_distribution<float> distX(0.0f, mWorldWidth);
    std::uniform_real_distribution<float> distY(0.0f, mWorldHeight);
    return { distX(mRandomGenerator), distY(mRandomGenerator) };
}

void Ecosystem::HandlePlantGrowth(float /*deltaTime*/) {
    // Les plantes peuvent générer de la nourriture ou se reproduire
    
}
