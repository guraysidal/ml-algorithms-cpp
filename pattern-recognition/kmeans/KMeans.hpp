#ifndef K_MEANS_HPP
#define K_MEANS_HPP

#include "../core/DataPoint.hpp"
#include <vector>
#include "../core/Metrics.hpp"

namespace pattern_recognition {

class KMeans {
private:
    int k_count; 
    int max_iterations; 
    std::vector<Datapoint> centroids; 

public:
    
    explicit KMeans(int k_value, int max_iter = 100);
    void fit(const std::vector<Datapoint>& dataset);
    int predict(const Datapoint& point) const;

    std::vector<Datapoint> getCentroids() const;
};

} // namespace pattern_recognition

#endif // K_MEANS_HPP