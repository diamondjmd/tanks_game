#pragma once

#include <cmath>
#include <string>

template <typename T>
class Point {
    public:
        Point() = default;
        inline Point(T x, T y) : x{x}, y{y} {};

        T x{};
        T y{};
        static constexpr double tolerance {0.0001};
};

//take two coordinates in the Cartesian coordinate system,
//and find the point directly in between both of them.
template <typename T, typename U>
inline Point<T> midPoint(const Point<T>& lhs, const Point<U>& rhs) {
    return {static_cast<T>((lhs.x + rhs.x) / 2), static_cast<T>( (lhs.y + rhs.y) / 2)};
}

template <typename T, typename U>
inline Point<T> operator-(const Point<T>& lhs, const Point<U>& rhs) {
    return {static_cast<T>(lhs.x - rhs.x), static_cast<T>(lhs.y - rhs.y)};
}

template <typename T, typename U>
inline Point<T> operator-(const Point<T>& lhs, const U scalar) {
    return {static_cast<T>(lhs.x - scalar), static_cast<T>(lhs.y -scalar)};
}

template <typename T, typename U>
inline Point<T> operator+(const Point<T>& lhs, const Point<U>& rhs) {
    return {static_cast<T>(lhs.x + rhs.x), static_cast<T>(lhs.y + rhs.y)};
}

template <typename T, typename U>
inline Point<T> operator+(const Point<T>& lhs, const U scalar) {
    return {static_cast<T>(lhs.x + scalar), static_cast<T>(lhs.y + scalar)};
}

template <typename T, typename U>
inline Point<T> operator*(const Point<T>& p, U scalar) {
    return {static_cast<T>(p.x * scalar), static_cast<T>(p.y * scalar)};
}

template <typename T, typename U>
inline Point<T> operator*(const Point<T>& lhs, const Point<U>& rhs) {
    return {static_cast<T>(lhs.x * rhs.x), static_cast<T>(lhs.y * rhs.y)};
}

template <typename T, typename U>
inline Point<T> operator/(const Point<T>& p, U scalar) {
    return {static_cast<T>(p.x / scalar), static_cast<T>(p.y / scalar)};
}

template <typename T, typename U>
inline T distance2(const Point<T>& lhs, const Point<U>& rhs) {
    const Point<T> delta = lhs - rhs;
    return static_cast<T>(delta.x * delta.x + delta.y * delta.y);
}

template <typename T, typename U>
inline Point<T>& operator+=(Point<T>& lhs, const Point<U>& rhs) {
     return lhs = lhs + rhs;
}

template <typename T, typename U>
inline Point<T>& operator-=(Point<T>& lhs, const Point<U>& rhs) {
    return lhs = lhs - rhs;
}

template <typename T, typename U>
inline bool operator==(const Point<T>& lhs, const Point<U>& rhs) {
    return std::abs(lhs.x - rhs.x) < Point<T>::tolerance && std::abs(lhs.y - rhs.y) < Point<T>::tolerance;
}

template <typename T, typename U>
inline bool operator!=(const Point<T>& lhs, const Point<U>& rhs) {
    return !(lhs == rhs);
}

template <typename T>
inline std::string toString(const Point<T>& point) {
    return "("+ std::to_string(point.x)+ "," +std::to_string(point.y)+")";
}

template <typename T>
inline std::ostream& operator<<(std::ostream& stream, const Point<T>& point) {
      return stream << toString(point);
}

// Normalize the vector
template <typename T>
inline Point<T> normalize(const Point<T>& vector){
    T magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (magnitude != 0.0) {
        return {static_cast<T>(vector.x / magnitude), static_cast<T>(vector.y / magnitude)};
    }
    // Handle division by zero or zero magnitude (return a default direction)
    return {static_cast<T>(1.0), static_cast<T>(0.0)};
}

// Helper function to create a Point<T> constexpr
template <typename T>
inline const Point<T> constPoint(const T x, const T y) {
    return Point<T>(x, y);
}

template <typename T>
inline Point<T> rotatePoint(const Point<T>& p, T thetaDegrees) {
    auto thetaRadians = thetaDegrees * M_PI / 180.0;
    return {static_cast<T>(p.x * std::cos(thetaRadians)), 
            static_cast<T>(p.y*  std::sin(thetaRadians))};
}
