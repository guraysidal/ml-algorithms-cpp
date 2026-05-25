#ifndef METRICS_HPP
#define METRICS_HPP

#include "DataPoint.hpp"
#include <cmath>
#include <stdexcept>

namespace pattern_recognition{
    template<typename T>
    inline T euclideanDistance(const Datapoint<T>& dp1, const Datapoint<T>& dp2){
        // Implementation for Euclidean distance calculation
        if(dp1.features.size() != dp2.features.size()){
            throw std::invalid_argument("Datapoint feature sizes must be equal!");
        }

        T sum = 0;
        
        for(size_t i = 0; i<dp1.features.size(); ++i){
           T diff = dp1.features[i]-dp2.features[i];
           sum += (diff * diff);
        }
        
        return static_cast<T>(std::sqrt(sum));
    }
}

#endif //METRICS_HPP