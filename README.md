MESSI MESSI BOOZ WINNER
25P905
ART NUMERIQUE INGENIEUR NIVEAU 1
🌍 Simulateur d'Écosystème Intelligent
📚 Description

Projet de Programmation Orientée Objet en C++ créant une simulation d’écosystème dynamique où herbivores, carnivores et plantes interagissent selon des règles biologiques.

🎯 Objectifs Pédagogiques

✅ Utilisation de namespaces pour l’organisation du code

✅ Utilisation de structs (Vector2D, Color, Food) pour les données simples

✅ Création de classes avec encapsulation (Entity, Ecosystem, GameEngine)

✅ Gestion mémoire sécurisée (constructeurs, destructeurs, smart pointers)

✅ Affichage graphique en temps réel avec SDL3

🏗 Architecture du Projet
Ecosystem::Core
 ├── Structs (Vector2D, Color, Food)
 ├── Entity (entités vivantes)
 ├── Ecosystem (gestionnaire de monde)
 └── GameEngine (boucle principale)

Ecosystem::Graphics
 └── Window (fenêtre SDL3)


Core → logique de l’écosystème

Graphics → affichage et interface

🚀 Installation
Prérequis

C++17 (g++ 9+, clang++ 10+, MSVC 2019+)

SDL3 (bibliothèque graphique)

Installation SDL3

Linux (Ubuntu/Debian):

sudo apt update
sudo apt install libsdl3-dev


macOS (Homebrew):

brew install sdl3


Windows:
Téléchargez SDL3 depuis libsdl.org

📦 Compilation
Avec Make (Linux/macOS)
make        # Compilation
make run    # Compilation + exécution
make clean  # Nettoyage

Sans Make (Toutes plateformes)
# Création des dossiers
mkdir -p obj/Core obj/Graphics bin

# Compilation
g++ -std=c++17 -Iinclude -c src/main.cpp -o obj/main.o
g++ -std=c++17 -Iinclude -c src/Core/*.cpp -o obj/Core/
g++ -std=c++17 -Iinclude -c src/Graphics/*.cpp -o obj/Graphics/

# Linking
g++ obj/main.o obj/Core/*.o obj/Graphics/*.o -o bin/ecosystem -lSDL3

# Exécution
./bin/ecosystem

🎮 Contrôles
Touche	Action
ESPACE	Pause / Reprise
R	Reset simulation
F	Ajouter nourriture
↑	Accélérer simulation
↓	Ralentir simulation
ÉCHAP	Quitter
🧪 Fonctionnalités
✅ Implémentées

Entités avec énergie, âge, mouvement

Reproduction quand énergie > 75%

Mort par faim ou vieillesse

Herbivores mangent plantes, carnivores chassent herbivores

Plantes produisent énergie (photosynthèse)

Affichage graphique SDL3 et statistiques temps réel

Contrôles utilisateur fonctionnels

🔮 Améliorations Possibles

Pathfinding intelligent (A*)

Comportements de fuite/poursuite

Mutations génétiques

Sauvegarde / Chargement d’état

Interface graphique (ImGui)

Graphiques de population

Biomes (eau, forêt, désert)

📊 Structure des Classes
Entity
class Entity {
private:
    float mEnergy;     // Énergie vitale
    int mAge;          // Âge en cycles
    bool mIsAlive;     // État vivant/mort
    EntityType mType;  // HERBIVORE / CARNIVORE / PLANT
public:
    void Update(float deltaTime);       // Mise à jour logique
    void Render(Renderer& renderer);    // Affichage graphique
    bool CanReproduce();                // Test reproduction
};

Ecosystem
class Ecosystem {
private:
    std::vector<std::unique_ptr<Entity>> mEntities;
    std::vector<Food> mFoodSources;
public:
    void Update(float deltaTime);
    void HandleEating();
    void HandleReproduction();
};

🐛 Dépannage

SDL3 not found

sudo apt install libsdl3-dev   # Linux
brew install sdl3               # macOS


Undefined reference to SDL_*
Ajoutez -lSDL3 aux flags de linking

Fenêtre ne s'affiche pas
Vérifiez l’installation de SDL3 :

sdl3-config --version



🎓 Résultat attendu

Console : affichage de l’initialisation et des statistiques

Fenêtre SDL3 :

🔵 Herbivores en mouvement

🔴 Carnivores chassant

🟢 Plantes immobiles

Barres d’énergie au-dessus des entités

Touches ESPACE, R, F fonctionnelles

✅ Ce que j'ai pigé de ce projet

Namespaces (Ecosystem::Core::Entity)

Structs (Vector2D, Color, Food)

Classes (Entity, Ecosystem, GameEngine, Window)

Encapsulation et getters

Constructeurs / Destructeurs et gestion mémoire

Smart Pointers (std::unique_ptr<Entity>)