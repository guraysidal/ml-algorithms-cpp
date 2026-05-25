#ifndef CSV_PARSER_HPP
#define CSV_PARSER_HPP

#include "DataPoint.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace pattern_recognition {

template <typename T>
class CSVParser {
public:
    static std::vector<Datapoint<T>> parse(const std::string& filename) {
        // Düzeltme: Datapoint yerine Datapoint<T> yazılmalı
        std::vector<Datapoint<T>> dataset; 

        std::ifstream MyCSVFile(filename);        
        if (!MyCSVFile.is_open()) {
            throw std::runtime_error("Dosya acilamadi: " + filename);
        }

        std::string line;
        std::getline(MyCSVFile, line); 
        
        while(getline(MyCSVFile,line)){
            if(line.empty()) continue;
            
            std::stringstream ss(line);
            std::string token; 
            std::vector<T> features;
            std::string label;

            while(std::getline(ss, token, ',')) {
                try{
                    T value = static_cast<T>(std::stod(token)); 
                    features.push_back(value);
                }catch(const std::invalid_argument& e){
                    label = token;
                }
            }
            Datapoint<T> dp(features, label); 
            dataset.push_back(dp);
        }
        return dataset;
    }
};

} // namespace pattern_recognition

#endif // CSV_PARSER_HPP