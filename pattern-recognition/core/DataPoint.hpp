#ifndef DATA_POINT_HPP
#define DATA_POINT_HPP
#include <vector>
#include <string>
#include <type_traits>

namespace pattern_recognition {
    template <typename T>
    struct Datapoint {
        static_assert(std::is_arithmetic<T>::value, "Datapoint can only be used with numeric types (int, float, double). Booleans or strings are not allowed!");        
        std::vector<T>features;
        std::string label;

        Datapoint(std::vector<T> f_in, const std::string l_in ="") : features(std::move(f_in)), label(std::move(l_in)) {}
    
    };
}

#endif //DATA_POINT_HPP