#include <iostream>
#include <vector>
#include <random>
#include <numeric>

std::vector<int> sampleVector(const std::vector<int>& objects, std::vector<double>& probabilities) {
    double sum = std::accumulate(probabilities.begin(), probabilities.end(), 0.0);
    
    for (auto& prob : probabilities) {
        prob /= sum;
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> distribution(probabilities.begin(), probabilities.end());
    
    std::vector<int> result;
    result.reserve(objects.size());
    
    for (size_t i = 0; i < objects.size(); ++i) {
        int index = distribution(gen);
        result.push_back(objects[index]);
    }
    
    return result;
}

int main() {
    std::vector<int> objects = {1, 2, 3, 4, 5};
    std::vector<double> probabilities = {0.2, 10, 0.1, 0.15, 0.25};
    
    std::vector<int> randomObjects = generateRandomVector(objects, probabilities);
    
    // Print the randomly selected objects
    for (const auto& obj : randomObjects) {
        std::cout << obj << " ";
    }
    std::cout << std::endl;
    
    return 0;
}

