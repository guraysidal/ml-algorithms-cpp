#include <iostream>
#include <vector>
#include "core/CSVParser.hpp"
#include "knn/KNNClassifier.hpp"

using namespace pattern_recognition;

int main() {
    std::cout << "Starting KNN Machine Learning Test...\n";
    std::cout << "-------------------------------------\n";

    try {
        // 1. Parse Dataset
        std::vector<Datapoint> dataset = CSVParser::parse("data/iris.csv");
        std::cout << "Dataset successfully parsed. Total records: " << dataset.size() << "\n";

        // 2. Initialize and Train Model (K = 3)
        KNNClassifier model(3);
        model.fit(dataset);
        std::cout << "Model trained successfully (data loaded into memory).\n";

        // 3. Create an Unlabeled Test Point
        // These features typically belong to the 'Iris-versicolor' class
        std::vector<double> unknown_features = {7.1, 3.1, 4.8, 1.4};
        Datapoint test_point(unknown_features, "UNKNOWN");

        // 4. Perform Prediction
        std::string predicted_label = model.predict(test_point);

        std::cout << "\n--- PREDICTION RESULT ---\n";
        std::cout << "Input Features: 7.1, 3.1, 4.8, 1.4\n";
        std::cout << "Model Prediction: -> " << predicted_label << " <-\n";

    } catch (const std::exception& e) {
        std::cerr << "EXCEPTION CAUGHT: " << e.what() << "\n";
    }

    std::cout << "-------------------------------------\n";
    return 0;
}