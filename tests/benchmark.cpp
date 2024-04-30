#include <iostream>
#include <chrono>
#include <cmath>

template <typename T>
struct Point {
    T x, y;
};


template <typename T>
inline Point<T> normalize(const Point<T>& vector) {
    T magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (magnitude != 0.0) {
        return {static_cast<T>(vector.x / magnitude), static_cast<T>(vector.y / magnitude)};
    }
    return {static_cast<T>(1.0), static_cast<T>(0.0)};
}

template <typename T>
inline Point<T> rotatePoint(const Point<T>& p, double thetaDegrees) {
    auto thetaRadians = thetaDegrees * M_PI / 180.0;
    const auto cosTheta = std::cos(thetaRadians);
    const auto sinTheta = std::sin(thetaRadians);
    return {static_cast<T>(p.x * cosTheta), static_cast<T>(p.y * sinTheta)};
}

void run_benchmark1() {
    std::cout << "Benchmark1:\n";
    // Create sample Point
    Point<double> samplePoint = {1.0, 2.0};

    // Benchmark normalize function
    auto startNormalize = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; ++i) {
        normalize(samplePoint);
    }
    auto endNormalize = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedNormalize = endNormalize - startNormalize;
    std::cout << "normalize elapsed time: " << elapsedNormalize.count() << " seconds\n";

    // Benchmark rotatePoint function
    auto startRotatePoint = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100000; ++i) {
        rotatePoint(samplePoint, 45.0);
    }
    auto endRotatePoint = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedRotatePoint = endRotatePoint - startRotatePoint;
    std::cout << "rotatePoint elapsed time: " << elapsedRotatePoint.count() << " seconds\n";
}