//
//  Assignment2.cpp
//  Random
//
//  Created by Kelson on 9/22/24.
//
#include <iostream>
#include <vector>
#include <format>
#include <random>
#include "distributions.hpp"

int main() {
    auto uniform = generateUniformDistribution(100000, 0, 159, 40);
    plotDistribution("--- Uniform ---", uniform, 80);

    auto normal = generateNormalDistribution(100000, 100, 15, 20);
    plotDistribution("--- Normal ---", normal, 80);

    auto poisson = generatePoissonDistribution(100000, 20, 20);
    plotDistribution("--- Poisson ---", poisson, 80);

    return 0;
}
