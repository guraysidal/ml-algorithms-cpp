#include <iostream>
#include <vector>
#include <ctime>
#include "core/CSVParser.hpp"
#include "knn/KNNClassifier.hpp"
#include "kmeans/KMeans.hpp"

using namespace pattern_recognition;

void runKNNTest(const std::vector<Datapoint>& dataset) {
    std::cout << "\n========================================\n";
    std::cout << "      [1] SUPERVISED LEARNING: KNN      \n";
    std::cout << "========================================\n";
    
    KNNClassifier model(3);
    model.fit(dataset);
    std::cout << "Model trained successfully.\n";

    std::vector<double> unknown_features = {7.1, 3.1, 4.8, 1.4};
    Datapoint test_point(unknown_features, "UNKNOWN");

    std::string predicted_label = model.predict(test_point);
    std::cout << "Input Features: 7.1, 3.1, 4.8, 1.4\n";
    std::cout << "Prediction -> " << predicted_label << "\n";
}

void runKMeansTest(const std::vector<Datapoint>& dataset) {
    std::cout << "\n========================================\n";
    std::cout << "     [2] UNSUPERVISED LEARNING: K-MEANS \n";
    std::cout << "========================================\n";
    
    KMeans model(3, 100);
    std::cout << "Training K-Means model with K=3...\n";
    model.fit(dataset);
    std::cout << "Model successfully converged!\n\n";

    std::vector<Datapoint> final_centroids = model.getCentroids();
    for (size_t i = 0; i < final_centroids.size(); ++i) {
        std::cout << final_centroids[i].label << " Center: [ ";
        for (double feature : final_centroids[i].features) {
            std::cout << feature << " ";
        }
        std::cout << "]\n";
    }
}

int main() {
    srand(time(NULL)); 
    std::cout << "Pattern Recognition Engine Started...\n";

    try {
        std::vector<Datapoint> dataset = CSVParser::parse("data/iris.csv");
        std::cout << "Dataset successfully parsed. Total records: " << dataset.size() << "\n";

        runKNNTest(dataset);
        runKMeansTest(dataset);

    } catch (const std::exception& e) {
        std::cerr << "EXCEPTION CAUGHT: " << e.what() << "\n";
    }

    std::cout << "\n========================================\n";
    std::cout << "All tests completed successfully.\n";
    return 0;
}