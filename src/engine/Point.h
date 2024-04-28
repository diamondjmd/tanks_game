#pragma once

#include <cmath>
#include <string>
#include <type_traits>


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
// template <typename T, typename U>
// inline Point<T> midPoint(const Point<T>& lhs, const Point<U>& rhs) {
//     return {static_cast<T>((lhs.x + rhs.x) / 2), static_cast<T>( (lhs.y + rhs.y) / 2)};
// }

// template <typename T, typename U>
// inline Point<decltype(T + U)>  midPoint(const Point<T>& lhs, const Point<U>& rhs) { 
//     return {(lhs.x + rhs.x) / 2, (lhs.y + rhs.y) / 2};
// }

// template <typename T, typename U>
// inline auto midPoint(const Point<T>& lhs, const Point<U>& rhs) -> decltype(lhs.x + rhs.x) {
//     return {(lhs.x + rhs.x) / 2, (lhs.y + rhs.y) / 2};
// }

template <typename T, typename U>
inline Point<typename std::common_type<T, U>::type> midPoint(const Point<T>& lhs, const Point<U>& rhs) { 
    return {(lhs.x + rhs.x) / 2, (lhs.y + rhs.y) / 2};
}

template <typename T, typename U>
inline Point<typename std::common_type<T, U>::type> operator-(const Point<T>& lhs, const Point<U>& rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

template <typename T, typename U>
inline Point<typename std::common_type<T, U>::type> operator-(const Point<T>& lhs, const U scalar) {
    return {lhs.x - scalar, lhs.y - scalar};
}

template <typename T, typename U>
inline Point<typename std::common_type<T, U>::type> operator+(const Point<T>& lhs, const Point<U>& rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

template <typename T, typename U>
inline Point<typename std::common_type<T, U>::type> operator+(const Point<T>& lhs, const U scalar) {
    return {lhs.x + scalar, lhs.y + scalar};
}

template <typename T, typename U>
inline Point<typename std::common_type<T, U>::type> operator*(const Point<T>& p, U scalar) {
    return {p.x * scalar, p.y * scalar};
}

template <typename T, typename U>
inline Point<typename std::common_type<T, U>::type> operator*(const Point<T>& lhs, const Point<U>& rhs) {
    return {lhs.x * rhs.x, lhs.y * rhs.y};
}

template <typename T, typename U>
inline Point<typename std::common_type<T, U>::type> operator/(const Point<T>& p, U scalar) {
    return {p.x / scalar, p.y / scalar};
}

template <typename T, typename U>
inline typename std::common_type<T, U>::type distance2(const Point<T>& lhs, const Point<U>& rhs) {
    const auto delta = lhs - rhs;
    return delta.x * delta.x + delta.y * delta.y;
}

template <typename T, typename U>
inline Point<typename std::common_type<T, U>::type>& operator+=(Point<T>& lhs, const Point<U>& rhs) {
     return lhs = lhs + rhs;
}

template <typename T, typename U>
inline Point<typename std::common_type<T, U>::type>& operator-=(Point<T>& lhs, const Point<U>& rhs) {
    return lhs = lhs - rhs;
}

template <typename T, typename U>
inline bool operator==(const Point<T>& lhs, const Point<U>& rhs) {
    return std::abs(lhs.x - rhs.x) < Point<T>::tolerance && 
           std::abs(lhs.y - rhs.y) < Point<T>::tolerance;
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
