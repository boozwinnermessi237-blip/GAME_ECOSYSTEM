#include "Structs.h"
#include <cmath>
#include <iostream>

// ===== Vector2D =====
Vector2D::Vector2D(float xValue, float yValue)
    : x(xValue), y(yValue) {}

float Vector2D::Distance(const Vector2D &other) const
{
    float dx = x - other.x;
    float dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}

Vector2D Vector2D::operator+(const Vector2D &other) const
{
    return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D &other) const
{
    return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator*(float s) const
{
    return Vector2D(x * s, y * s);
}

float Vector2D::length() const
{
    return std::sqrt(x * x + y * y);
}

Vector2D Vector2D::Normalize() const
{
    float len = length();
    return (len > 0) ? Vector2D(x / len, y / len) : Vector2D(0, 0);
}

void Vector2D::Print() const
{
    std::cout << "Vector2D(" << x << ", " << y << ")" << std::endl;
}

// ===== Color =====
Color::Color() : r(255), g(255), b(255), a(255) {}

Color::Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha)
    : r(red), g(green), b(blue), a(alpha) {}

Color Color::Red()       { return Color(255, 0, 0); }
Color Color::Green()     { return Color(0, 255, 0); }
Color Color::Blue()      { return Color(0, 100, 255); }
Color Color::Yellow()    { return Color(255, 255, 0); }
Color Color::White()     { return Color(255, 255, 255); }
Color Color::Black()     { return Color(0, 0, 0); }
Color Color::DarkGreen() { return Color(0, 150, 0); }

void Color::Print() const
{
    std::cout << "Color(" << (int)r << ", " << (int)g << ", " << (int)b << ", " << (int)a << ")" << std::endl;
}

// ===== Food =====
Food::Food(Vector2D pos, float energy)
    : position(pos), energyValue(energy), color(Color::DarkGreen()), isConsumed(false) {}
