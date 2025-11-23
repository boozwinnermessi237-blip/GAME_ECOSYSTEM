// Entity.cpp 
#include "Entity.h"
#include <iostream>
#include <cmath>
#include <SDL3/SDL.h>

using namespace Ecosystem::Core;

// CONSTRUCTEURS

Entity::Entity(EntityType type, Vector2D pos, std::string entityName)
    : mType(type),
      position(pos),
      name(entityName),
      size(10.0f),
      mEnergy(100.0f),
      mMaxEnergy(100.0f),
      mAge(0),
      mMaxAge(500),
      mIsAlive(true),
      mVelocity({0.0f, 0.0f})
{
    std::random_device rd;
    mRandomGenerator.seed(rd());

    // Couleur par défaut selon le type
    switch (type) {
        case EntityType::HERBIVORE: color = { 0, 255, 0, 255 }; break;
        case EntityType::CARNIVORE: color = { 255, 0, 0, 255 }; break;
        case EntityType::PLANT:     color = { 0, 180, 0, 255 }; break;
    }
}

Entity::Entity(const Entity& other)
    : mType(other.mType),
      position(other.position),
      name(other.name + "_copy"),
      size(other.size),
      mEnergy(other.mEnergy),
      mMaxEnergy(other.mMaxEnergy),
      mAge(0),                     // Bébé → repart à 0
      mMaxAge(other.mMaxAge),
      mIsAlive(true),
      mVelocity(other.mVelocity)
{
    std::random_device rd;
    mRandomGenerator.seed(rd());
}

Entity::~Entity() {
    // Rien de particulier, mais on laisse pour debug
    // std::cout << name << " détruit.\n";
}

// Augmente

void Entity::Update(float deltaTime, float worldWidth, float worldHeight) {
    if (!mIsAlive) return;

    Age(deltaTime);
    ConsumeEnergy(deltaTime);
    Move(deltaTime, worldWidth, worldHeight);
    CheckVitality();
}

// 🚶 DÉPLACEMENT

Vector2D Entity::GenerateRandomDirection() {
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    return { dist(mRandomGenerator), dist(mRandomGenerator) };
}

void Entity::Move(float deltaTime, float worldWidth, float worldHeight) {
    // Les plantes ne bougent pas
    if (mType == EntityType::PLANT) return;

    Vector2D dir = GenerateRandomDirection();

    mVelocity.x = dir.x * 30.0f;
    mVelocity.y = dir.y * 30.0f;

    position.x += mVelocity.x * deltaTime;
    position.y += mVelocity.y * deltaTime;

    WrapAroundWorld(worldWidth, worldHeight);
}

void Entity::WrapAroundWorld(float worldWidth, float worldHeight) {
    if (position.x < 0) position.x = worldWidth;
    if (position.x > worldWidth) position.x = 0;
    if (position.y < 0) position.y = worldHeight;
    if (position.y > worldHeight) position.y = 0;
}

// ÉNERGIe

void Entity::ConsumeEnergy(float deltaTime) {
    mEnergy -= 2.0f * deltaTime;

    if (mEnergy < 0)
        mEnergy = 0;
}

void Entity::Eat(float energy) {
    mEnergy += energy;
    if (mEnergy > mMaxEnergy) mEnergy = mMaxEnergy;
}

// REPRODUCTION

bool Entity::CanReproduce() const {
    return mEnergy > (mMaxEnergy * 0.8f);
}

std::unique_ptr<Entity> Entity::Reproduce() {
    if (!CanReproduce()) return nullptr;

    mEnergy *= 0.5f; // L’énergie est divisée entre les 2

    return std::make_unique<Entity>(*this);
}

// Fonction veillissement 

void Entity::Age(float deltaTime) {
    mAge += 1 * deltaTime;
}

void Entity::CheckVitality() {
    if (mAge > mMaxAge || mEnergy <= 0)
        mIsAlive = false;
}

// Ce que le SDL doit montrer sur l'interface

void Entity::Render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_FRect rect;
    rect.w = size;
    rect.h = size;
    rect.x = position.x - size / 2;
    rect.y = position.y - size / 2;

    SDL_RenderFillRect(renderer, &rect);
}

// AFFICHAGE CONSOLE

void Entity::Afficher() const {
    std::cout << "Entity " << name
              << " | Energy: " << mEnergy
              << " | Age: " << mAge
              << " | Alive: " << mIsAlive
              << "\n" << std::endl;
}
