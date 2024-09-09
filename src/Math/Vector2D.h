#pragma once
#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "pch.h"

template <typename T>
class Vector2D {

    public:
        Vector2D(T x = 0, T y = 0) : x(x), y(y) {}

        inline T getX() { return x; }
        inline T getY() { return y; }

        inline void setX(T x) { this->x = x; }
        inline void setY(T y) { this->y = y; }

        inline void translate(T dx, T dy) {
            x += dx;
            y += dy;
        }

        inline Vector2D operator+(const Vector2D& v2) const {
            return Vector2D(x + v2.x, y + v2.y);
        }

        inline Vector2D operator-(const Vector2D& v2) const {
            return Vector2D(x - v2.x, y - v2.y);
        }

        inline Vector2D operator*(T scalar) {
            return Vector2D(x * scalar, y * scalar);
        }

        inline Vector2D operator/(T scalar) {
            return Vector2D(x / scalar, y / scalar);
        }

        inline Vector2D& operator+=(const Vector2D& v2) {
            x += v2.x;
            y += v2.y;

            return *this;
        }

        inline Vector2D& operator-=(const Vector2D& v2) {
            x -= v2.x;
            y -= v2.y;

            return *this;
        }

        inline Vector2D& operator*=(T scalar) {
            x *= scalar;
            y *= scalar;

            return *this;
        }

        inline Vector2D& operator/=(T scalar) {
            x /= scalar;
            y /= scalar;

            return *this;
        }

        void log(std::string msg = "") {
            std::cout << msg << "(x, y) : " << "(" << x << ", " << y << ")" << std::endl;
        }

    private:
        T x;
        T y;

};

#endif // VECTOR2D_H