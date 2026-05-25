#ifndef K_MEANS_HPP
#define K_MEANS_HPP

#include "../core/DataPoint.hpp"
#include <vector>
#include "../core/Metrics.hpp"
#include <limits>

namespace pattern_recognition {

template<typename T>
class KMeans {
private:
    int k_count; 
    int max_iterations; 
    std::vector<Datapoint<T>> centroids; 

public:
    KMeans(int k_value, int max_iter) : k_count(k_value), max_iterations(max_iter){}
    void fit(const std::vector<Datapoint<T>>& dataset) {
        if (dataset.empty()) return;

        // 1. Get the number of features dynamically (e.g., 4 for Iris dataset)
        size_t num_features = dataset[0].features.size();
    
        // 2. Initial assignments (Initialize with -1 indicating no cluster assigned yet)
        std::vector<int> assignments(dataset.size(), -1);
    
        // 3. Select UNIQUE random initial centroids
        std::vector<int> chosen_indices;
        while (centroids.size() < k_count) {
            int randomIndex = rand() % dataset.size();
        
        
            if (std::find(chosen_indices.begin(), chosen_indices.end(), randomIndex) == chosen_indices.end()) {
                chosen_indices.push_back(randomIndex);
            
                Datapoint<T> initial_centroid = dataset[randomIndex];
                initial_centroid.label = "Cluster_" + std::to_string(centroids.size()); 
                centroids.push_back(initial_centroid);
            }
        }

        // --- MAIN ITERATION LOOP ---
        for(int iter = 0; iter < max_iterations; iter++) {
            bool changed = false; // Convergence flag

            // STEP A: Assignment (E-Step) - Find the closest centroid for each point
            for(size_t n = 0; n < dataset.size(); n++) {
                double minDistance = std::numeric_limits<T>::max(); 
                int best_k = 0;
            
                // ... Loop through centroids and find the minimum distance ...
                for(size_t k = 0; k<k_count;k++){
                    T distance =  euclideanDistance(dataset[n],centroids[k]);
                    if(distance < minDistance){
                        minDistance = distance;
                        best_k = k;
                    }
                }

                // If the assigned cluster for this data point changes:
                if(assignments[n] != best_k) {
                    assignments[n] = best_k;
                    changed = true; // The system has not converged yet
                }
            }

            
    

            // CONVERGENCE CHECK
            if(!changed) {
                // If no assignments changed, the algorithm has converged.
                // We can break the loop early before reaching max_iterations.
                break; 
            }

            // STEP B: Refitting (M-Step) - Calculate new centroids
            // HINT: Use a 2D vector for sumFeatures and a 1D vector for assignmentCounts.
            // std::vector<std::vector<double>> sumFeatures(k_count, std::vector<double>(num_features, 0.0));
            // std::vector<int> assignmentCounts(k_count, 0);
            std::vector<std::vector<T>> sumFeatures(k_count,std::vector<T>(num_features,0.0));
            std::vector<int> assigmentCounts(k_count,0);
        
            for(size_t n = 0; n<dataset.size();n++){
                int k = assignments[n];
                if(k!=-1){
                    assigmentCounts[k]++;
                    for(size_t f = 0; f<dataset[n].features.size(); f++){
                        sumFeatures[k][f] += dataset[n].features[f];
                    }
                }
            }
        

            for(size_t k = 0; k<k_count; k++){
                if(assigmentCounts[k]>0){
                    for(size_t f = 0; f<dataset[0].features.size(); f++){
                        double meanCluster = sumFeatures[k][f] / assigmentCounts[k];
                        centroids[k].features[f] = meanCluster;
                    }
                }
            }
        }

    
    }

    int predict(const Datapoint<T>& point) const{
        double minDistance = std::numeric_limits<T>::max();
        int best_k = 0;

        for(size_t k = 0; k<centroids.size();k++){
            T distance =  euclideanDistance(point,centroids[k]);
            if(distance < minDistance){
                minDistance = distance;
                best_k = k;
            }
        }
        return best_k;
    }

    std::vector<Datapoint<T>> getCentroids() const{
        return centroids;
    }   
};

} // namespace pattern_recognition

#endif // K_MEANS_HPP