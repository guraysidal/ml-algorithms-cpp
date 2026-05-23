#ifndef KNN_CLASSIFIER_HPP
#define KNN_CLASSIFIER_HPP

#include "../core/DataPoint.hpp"
#include <vector>
#include <string>

namespace pattern_recognition {

class KNNClassifier {
private:
    int k; 
    std::vector<Datapoint> training_data; 

public:
   
    explicit KNNClassifier(int k_value = 3);

    void fit(const std::vector<Datapoint>& dataset);

    std::string predict(const Datapoint& unclassified_point) const;
};

} // namespace pattern_recognition

#endif // KNN_CLASSIFIER_HPP