#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <string>
#include <iostream>

class Vector2D {

    public:
        Vector2D(float x, float y) : x(x), y(y) {}

        inline float getX() { return x; }
        inline float getY() { return y; }

        inline void setX(float x) { this->x = x; }
        inline void setY(float y) { this->y = y; }

        inline Vector2D operator+(const Vector2D& v2) const {
            return Vector2D(x + v2.x, y + v2.y);
        }

        inline Vector2D operator-(const Vector2D& v2) const {
            return Vector2D(x - v2.x, y - v2.y);
        }

        inline Vector2D operator*(float scalar) {
            return Vector2D(x * scalar, y * scalar);
        }

        inline Vector2D operator/(float scalar) {
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

        inline Vector2D& operator*=(float scalar) {
            x *= scalar;
            y *= scalar;

            return *this;
        }

        inline Vector2D& operator/=(float scalar) {
            x /= scalar;
            y /= scalar;

            return *this;
        }

        void log(std::string msg = "") {
            std::cout << msg << "(x, y) : " << "(" << x << ", " << y << ")" << std::endl;
        }

    private:
        float x;
        float y;

};

#endif // VECTOR2D_H