#ifndef DATA_POINT_HPP
#define DATA_POINT_HPP
#include <vector>
#include <string>

namespace pattern_recognition {
    struct Datapoint {
        std::vector<double>features;
        std::string label;

        Datapoint(std::vector<double> f, std::string l) : features(std::move(f)), label(std::move(l)) {}
    
    };
}

#endif //DATA_POINT_HPP