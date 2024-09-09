#pragma once
#ifndef POINT_H
#define POINT_H

template <typename T>
class Point {
    public:
        Point(T x = 0, T y = 0) : x(x), y(y) {}

        inline T getX() { return x; }
        inline T getY() { return y; }

        inline void setX(T x) { this->x = x; }
        inline void setY(T y) { this->y = y; }

        inline Point operator+(const Point& p2) const {
            return Point(x + p2.x, y + p2.y);
        }

        inline Point operator-(const Point& p2) const {
            return Point(x - p2.x, y - p2.y);
        }

        inline Point operator*(T scalar) {
            return Point(x * scalar, y * scalar);
        }

        inline Point operator/(T scalar) {
            return Point(x / scalar, y / scalar);
        }

        inline Point& operator+=(const Point& p2) {
            x += p2.x;
            y += p2.y;

            return *this;
        }

        inline Point& operator-=(const Point& p2) {
            x -= p2.x;
            y -= p2.y;

            return *this;
        }

        inline Point& operator*=(T scalar) {
            x *= scalar;
            y *= scalar;

            return *this;
        }

        inline Point& operator/=(T scalar) {
            x /= scalar;
            y /= scalar;

            return *this;
        }

        template <typename U>
        explicit operator Point<U>() const {
            return Point<U>(static_cast<U>(x), static_cast<U>(y));
        }

    private:
        T x, y;
};

#endif // POINT_H