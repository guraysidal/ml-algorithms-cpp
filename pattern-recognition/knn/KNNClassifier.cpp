#include "../core/Metrics.hpp"
#include "KNNClassifier.hpp"
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <stdexcept>

namespace pattern_recognition {
KNNClassifier::KNNClassifier(int k) : k(k){
    if(k <= 0)
        throw std::invalid_argument("Cluster count should be greater than zero. ");

}

void KNNClassifier::fit(const std::vector<Datapoint>& dataset){
    training_data = dataset;
}

std::string KNNClassifier::predict(const Datapoint& unclassified_point) const{
    std::vector<std::pair<double,std::string>> distances;

    for(const Datapoint& dp: training_data){
        double distance = euclideanDistance(unclassified_point,dp);
        std::pair<double,std::string> distanceLabel(distance,dp.label);
        distances.push_back(distanceLabel);
    }

    std::sort(distances.begin(), distances.end());

    std::unordered_map<std::string, int> vote_counts;
    for(size_t k_index = 0 ; k_index<k; ++k_index){
        vote_counts[distances[k_index].second]++;
    }

    std::string best_label = "";
    int max_votes = -1;

    for(const auto& pair : vote_counts){
        if(pair.second >max_votes){
            max_votes = pair.second;
            best_label = pair.first;
        }
    }
    
    return best_label;
};

}
