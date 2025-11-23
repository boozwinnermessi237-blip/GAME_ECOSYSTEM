
#pragma once
#include "Structs.h"
#include <SDL3/SDL.h>
#include <string>
#include <random>
#include <memory>

namespace Ecosystem {
namespace Core {

// Types d'entités
enum class EntityType {
    HERBIVORE,
    CARNIVORE,
    PLANT
};

class Entity {
private:
    //  Données privées
    float mEnergy;
    float mMaxEnergy;
    int mAge;
    int mMaxAge;
    bool mIsAlive;
    Vector2D mVelocity;
    EntityType mType;

    // Générateur aléatoire
    mutable std::mt19937 mRandomGenerator;

public:
    //  Données publiques
    Vector2D position;
    Color color;
    float size;
    std::string name;

    //  Constructeurs
    Entity(EntityType type, Vector2D pos, std::string entityName = "Unnamed");
    Entity(const Entity& other); // Constructeur de copie

    //  Destructeur
    ~Entity();

    //  Méthodes publiques
    void Update(float deltaTime, float worldWidth, float worldHeight);
    void Move(float deltaTime, float worldWidth, float worldHeight);
    void Eat(float energy);
    bool CanReproduce() const;
    std::unique_ptr<Entity> Reproduce();

    //  Getters
    float GetEnergy() const { return mEnergy; }
    float GetEnergyPercentage() const { return mEnergy / mMaxEnergy; }
    int GetAge() const { return mAge; }
    bool IsAlive() const { return mIsAlive; }
    EntityType GetType() const { return mType; }
    Vector2D GetVelocity() const { return mVelocity; }

    //  Rendu SDL
    void Render(SDL_Renderer* renderer) const;

    //  Debug console
    void Afficher() const;

private:
    // Méthodes internes
    void ConsumeEnergy(float deltaTime);
    void Age(float deltaTime);
    void CheckVitality();
    Vector2D GenerateRandomDirection();
    void WrapAroundWorld(float worldWidth, float worldHeight);
    Color CalculateColorBasedOnState() const;
};

} // namespace Core
} // namespace Ecosystem
