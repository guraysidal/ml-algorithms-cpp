#ifndef METRICS_HPP
#define METRICS_HPP

#include "DataPoint.hpp"
#include <cmath>
#include <stdexcept>

namespace pattern_recognition{
    inline double euclideanDistance(const Datapoint& dp1, const Datapoint& dp2){
        // Implementation for Euclidean distance calculation
        if(dp1.features.size() != dp2.features.size()){
            throw std::invalid_argument("Datapoint feature sizes must be equal!");
        }

        double sum = 0.0;
        
        for(size_t i = 0; ){
            for(double f2 : dp2.features){
                sum+=std::pow((f1-f2),2);
            }
        }
        
        return sum;
    }
}



#endif //METRICS_HPP