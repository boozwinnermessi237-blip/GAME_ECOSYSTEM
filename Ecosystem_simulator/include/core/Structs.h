#ifndef STRUCTS_H
#define STRUCTS_H

#include <cmath>
#include <cstdint>
#include <iostream>


// Vector2D
struct Vector2D
{
    float x;
    float y;

    // Constructeur
    Vector2D(float xValue = 0.0f, float yValue = 0.0f)
        : x(xValue), y(yValue) {}

    // Distance entre deux vecteurs
    float Distance(const Vector2D &other) const
    {
        float dx = x - other.x;
        float dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    // Opérateurs mathématiques
    Vector2D operator+(const Vector2D &other) const
    {
        return Vector2D(x + other.x, y + other.y);
    }

    Vector2D operator-(const Vector2D &other) const
    {
        return Vector2D(x - other.x, y - other.y);
    }

    Vector2D operator*(float s) const
    {
        return Vector2D(x * s, y * s);
    }

    // Norme
    float length() const
    {
        return std::sqrt(x * x + y * y);
    }

    // Normalisation
    Vector2D Normalize() const
    {
        float len = length();
        return (len > 0) ? Vector2D(x / len, y / len) : Vector2D(0, 0);
    }

    void Print() const
    {
        std::cout << "Vector2D(" << x << ", " << y << ")\n" <<std::endl;
    }
};


// Structure Color 
struct Color
{
    std::uint8_t r, g, b, a;

    // Constructeur par défaut : blanc
    Color()
        : r(255), g(255), b(255), a(255) {}

    // Constructeur personnalisé
    Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = 255)
        : r(red), g(green), b(blue), a(alpha) {}

    // Couleurs prédéfinies
    static Color Red()       { return Color(255,   0,   0); }
    static Color Green()     { return Color(  0, 255,   0); }
    static Color Blue()      { return Color(  0, 100, 255); }
    static Color Yellow()    { return Color(255, 255,   0); }
    static Color White()     { return Color(255, 255, 255); }
    static Color Black()     { return Color(  0,   0,   0); }
    static Color DarkGreen() { return Color(  0, 150,   0); }

    void Print() const
    {
        std::cout << "Color(" << (int)r << ", " << (int)g
                  << ", " << (int)b << ", " << (int)a << ")\n" <<std::endl;
    }
};

// Food
struct Food
{
    Vector2D position;
    float energyValue;
    Color color;
    bool isConsumed;

    // Constructeur
    Food(Vector2D pos = Vector2D(), float energy = 25.0f)
        : position(pos),
          energyValue(energy),
          color(Color::DarkGreen()),
          isConsumed(false)
    {}
};

#endif // STRUCTS_H
