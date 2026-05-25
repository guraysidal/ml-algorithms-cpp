#ifndef KNN_CLASSIFIER_HPP
#define KNN_CLASSIFIER_HPP

#include "../core/DataPoint.hpp"
#include <vector>
#include <string>
#include <algorithm> 
#include <unordered_map> 
#include <stdexcept>

namespace pattern_recognition {

template <typename T>
class KNNClassifier {
private:
    int k; 
    std::vector<Datapoint<T>> training_data; 

public:
   
    explicit KNNClassifier(int k_value = 3) : k(k_value){
        if(k <= 0)
            throw std::invalid_argument("Cluster count should be greater than zero. ");
    }

    void fit(const std::vector<Datapoint<T>>& dataset){
        training_data = dataset;
    }

    std::string predict(const Datapoint<T>& unclassified_point) const{
        std::vector<std::pair<T,std::string>> distances;

        for(const auto& dp: training_data){
            T distance = euclideanDistance(unclassified_point,dp);
            std::pair<T,std::string> distanceLabel(distance,dp.label);
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
};

} // namespace pattern_recognition

#endif // KNN_CLASSIFIER_HPP