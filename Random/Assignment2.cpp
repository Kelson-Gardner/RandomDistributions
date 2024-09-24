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


class DistributionPair
{
  public:
    DistributionPair(std::uint32_t minValue, std::uint32_t maxValue) :
        minValue(minValue),
        maxValue(maxValue),
        count(0)
    {
    }

    std::uint32_t minValue;
    std::uint32_t maxValue;
    std::uint32_t count;
};

std::vector<DistributionPair> generateUniformDistribution(std::uint32_t howMany, std::uint32_t min, std::uint32_t max, std::uint8_t numberBins);
std::vector<DistributionPair> generateNormalDistribution(std::uint32_t howMany, float mean, float stdev, std::uint8_t numberBins);
std::vector<DistributionPair> generatePoissonDistribution(std::uint32_t howMany, std::uint8_t howOften, std::uint8_t numberBins);
void test();
void plotDistribution(std::string title, const std::vector<DistributionPair>& distribution, const std::uint8_t maxPlotLineSize);

int main() {
    auto normal = generateNormalDistribution(100000, 50, 5.0, 40);
    auto uniform = generateUniformDistribution(100000, 0, 79, 40);
    auto poisson = generatePoissonDistribution(100000, 6, 40);
    plotDistribution("--- Uniform ---", uniform, 80);
    plotDistribution("--- Normal ---", normal, 80);
    plotDistribution("--- Poisson ---", poisson, 80);
    test();
    return 0;
}

void plotDistribution(std::string title, const std::vector<DistributionPair>& distribution, const std::uint8_t maxPlotLineSize){
    std::cout << title << std::endl;
    std::uint32_t max = 0;
    for(DistributionPair pair : distribution){
        if(pair.count > max){
            max = pair.count;
        }
    }
    for(DistributionPair pair : distribution){
        auto pairInfo = std::format("Range [ {:>2}, {:>2}] : ", pair.minValue, pair.maxValue);
        std::cout << pairInfo;
        int range = (static_cast<float>(pair.count) / static_cast<float>(max)) * maxPlotLineSize;
        for(int i = 0; i < range; i++){
            std::cout << "*";
        }
        std::cout << "\n";
    }
}

std::vector<DistributionPair> generateUniformDistribution(std::uint32_t howMany, std::uint32_t min, std::uint32_t max, std::uint8_t numberBins){
    std::random_device rd;
    std::default_random_engine engine{rd()};
    std::uniform_int_distribution<int> dist(min, max);
    int range = (max + 1 - min) / numberBins;
    int index = min;
    std::vector<DistributionPair> pairs;
    for(std::uint8_t i = 0; i < numberBins; i++){
        DistributionPair pair(index, index + range - 1);
        pairs.push_back(pair);
        index += range;
    }
    
    for(std::uint32_t i = 0; i < howMany; i++){
        std::uint32_t randomNumber = dist(engine);
        if(randomNumber < min){
            pairs[0].count += 1;
        } else if(randomNumber > max){
            pairs[pairs.size()].count += 1;
        } else {
            int vectorIndex = (randomNumber - min) / range;
            pairs[vectorIndex].count += 1;
        }
    }

    return pairs;
}

std::vector<DistributionPair> generateNormalDistribution(std::uint32_t howMany, float mean, float stdev, std::uint8_t numberBins){
    std::random_device rd;
    std::default_random_engine engine{rd()};
    float min = mean - 4 * stdev;
    float max = mean + 4 * stdev - 1;
    std::normal_distribution<double> dist(mean, stdev);
    int range = (max + 1 - min) / numberBins;
    int index = min;
    std::vector<DistributionPair> pairs;

    for(std::uint8_t i = 0; i < numberBins; i++){
        DistributionPair pair(index, index + range - 1);
        pairs.push_back(pair);
        index += range;
    }

    for(std::uint32_t i = 0; i < howMany; i++){
        int randomNumber = dist(engine);
        if(randomNumber < min){
            pairs[0].count += 1;
        } else if(randomNumber > max){
            pairs[pairs.size() - 1].count += 1;
        } else {
            int vectorIndex = (randomNumber - min) / range;
            pairs[vectorIndex].count += 1;
        }
    }

    return pairs;
}

std::vector<DistributionPair> generatePoissonDistribution(std::uint32_t howMany, std::uint8_t howOften, std::uint8_t numberBins){
    std::random_device rd;
    std::default_random_engine engine{rd()};
    std::poisson_distribution<int> dist(howOften);
    std::vector<DistributionPair> pair;
    std::vector<DistributionPair> pairs;
    int index = 0;
    int range = 1;
    for(std::uint8_t i = 0; i < numberBins; i++){
        DistributionPair pair(index, index + range - 1);
        pairs.push_back(pair);
        index += range;
    }

    for(std::uint32_t i = 0; i < howMany; i++){
        int randomNumber = dist(engine);
        if(randomNumber < 0){
            pairs[0].count += 1;
        } else if(randomNumber > numberBins){
            pairs[pairs.size() - 1].count += 1;
        } else {
            int vectorIndex = randomNumber / range;
            pairs[vectorIndex].count += 1;
        }
    }

    return pairs;
}

// ------------------------------------------------------------------
//
// Testing Code
//
// ------------------------------------------------------------------
#include <functional>
#include <iostream>
#include <numeric>
#include <string>

namespace testing::detail
{
    using namespace std::string_literals;

    using Bins = std::vector<std::pair<std::uint32_t, std::uint32_t>>;
    using DistFunc = std::function<std::vector<DistributionPair>()>;

#define CS3460_ASSERT_EQ(expected, actual, message)                    \
    if (expected != actual)                                            \
    {                                                                  \
        fail(message, "[ Expected", expected, "but got", actual, "]"); \
        return;                                                        \
    }

#define CS3460_CASE(x) \
    [] {               \
        return x;      \
    };                 \
    std::cout << " Case " << #x << "\n";

    template <typename Message>
    void failInternal(const Message& message)
    {
        std::cout << message << " ";
    }

    template <typename Message, typename... Messages>
    void failInternal(const Message& message, const Messages&... messages)
    {
        failInternal(message);
        failInternal(messages...);
    }

    template <typename... Messages>
    void fail(const Messages&... messages)
    {
        std::cout << "  Assertion failed: ";
        failInternal(messages...);
        std::cout << "\n";
    }

    Bins generateBins(const std::uint32_t min, const std::uint32_t max, const std::uint8_t numberBins)
    {
        const auto binRange = (max - min) / numberBins;
        auto minBin = min;
        auto maxBin = min + binRange;

        Bins results(numberBins);
        for (std::uint8_t bin = 0u; bin < numberBins; bin++)
        {
            results[bin] = { minBin, maxBin };
            minBin = maxBin + 1;
            maxBin = minBin + binRange;
        }

        return results;
    }

    void returnsTheExpectedBins(const DistFunc& func, const Bins& bins)
    {
        const auto result = func();
        CS3460_ASSERT_EQ(bins.size(), result.size(), "Wrong number of bins");
        for (auto i = 0u; i < bins.size(); i++)
        {
            CS3460_ASSERT_EQ(bins[i].first, result[i].minValue, "Wrong minimum value for bin "s + std::to_string(i));
            CS3460_ASSERT_EQ(bins[i].second, result[i].maxValue, "Wrong maximum value for bin "s + std::to_string(i));
        }
    }

    void hasTheCorrectTotalAcrossAllBins(const DistFunc& func, const std::uint32_t howMany)
    {
        const auto result = func();
        const auto add_counts = [](std::uint32_t total, const DistributionPair& bin)
        {
            return total + bin.count;
        };
        CS3460_ASSERT_EQ(howMany, std::accumulate(result.cbegin(), result.cend(), 0u, add_counts),
                         "Wrong number of elements across all bins");
    }

    void testUniformDistribution()
    {
        std::cout << "Testing generateUniformDistribution\n";
        auto func = CS3460_CASE(generateUniformDistribution(100000, 0, 79, 40));
        returnsTheExpectedBins(func, generateBins(0, 79, 40));
        hasTheCorrectTotalAcrossAllBins(func, 100000);

        auto func2 = CS3460_CASE(generateUniformDistribution(0, 50, 59, 10));
        returnsTheExpectedBins(func2, generateBins(50, 59, 10));

        auto func3 = CS3460_CASE(generateUniformDistribution(0, 0, 79, 40));
        hasTheCorrectTotalAcrossAllBins(func3, 0);

        auto func4 = CS3460_CASE(generateUniformDistribution(100000, 0, 79, 1));
        hasTheCorrectTotalAcrossAllBins(func4, 100000);
    }

    void testNormalDistribution()
    {
        std::cout << "Testing generateNormalDistribution\n";
        auto func = CS3460_CASE(generateNormalDistribution(100000, 50, 5, 40));
        returnsTheExpectedBins(func, generateBins(30, 69, 40));
        hasTheCorrectTotalAcrossAllBins(func, 100000);

        auto func2 = CS3460_CASE(generateNormalDistribution(0, 50, 5, 40));
        hasTheCorrectTotalAcrossAllBins(func2, 0);

        auto func3 = CS3460_CASE(generateNormalDistribution(100000, 20.5, 1.125, 9));
        returnsTheExpectedBins(func3, generateBins(16, 24, 9));
        hasTheCorrectTotalAcrossAllBins(func3, 100000);
    }

    void testPoissonDistribution()
    {
        std::cout << "Testing generatePoissonDistribution\n";
        auto func = CS3460_CASE(generatePoissonDistribution(100000, 6, 40));
        returnsTheExpectedBins(func, generateBins(0, 39, 40));
        hasTheCorrectTotalAcrossAllBins(func, 100000);

        auto func2 = CS3460_CASE(generatePoissonDistribution(0, 6, 40));
        hasTheCorrectTotalAcrossAllBins(func2, 0);

        auto func3 = CS3460_CASE(generatePoissonDistribution(100000, 255, 40));
        hasTheCorrectTotalAcrossAllBins(func3, 100000);
    }
} // namespace testing::detail

void test()
{
    using namespace testing::detail;

    testUniformDistribution();
    testNormalDistribution();
    testPoissonDistribution();

    std::cout << "\n\n";
}
