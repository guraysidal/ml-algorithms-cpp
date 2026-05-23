#include "CSVParser.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace pattern_recognition {

    std::vector<Datapoint> CSVParser::parse(const std::string& filename) {
        std::vector<Datapoint> dataset;

        // 1. Adım: std::ifstream ile dosyayı aç ve açılıp açılmadığını kontrol et (açılmadıysa throw kullan)
        std::ifstream MyCSVFile(filename);        
        
        if (!MyCSVFile.is_open()) {
            throw std::runtime_error("Dosya acilamadi: " + filename);
        }

        std::string line;
        std::getline(MyCSVFile, line); 
        
        // 3. Adım: while döngüsü ile dosyanın sonuna kadar satır satır oku
        while(getline(MyCSVFile,line)){
            if(line.empty()) continue;
            
            std::stringstream ss(line);
            std::string token; // Virgüllerin arasındaki her bir kelimeyi/sayıyı tutacağımız geçici değişken
            std::vector<double> features;
            std::string label;

            while(std::getline(ss, token, ',')) {
                try{
                    double value = std::stod(token);
                    features.push_back(value);
                }catch(const std::invalid_argument& e){
                    label = token;
                }
            }
            Datapoint dp(features,label);
            dataset.push_back(dp);
        }
        return dataset;
    }

} // namespace pattern_recognition