// CSVParser.hpp
#ifndef CSV_PARSER_HPP
#define CSV_PARSER_HPP

#include "DataPoint.hpp"
#include <vector>
#include <string>

namespace pattern_recognition {

class CSVParser {
public:
    
    static std::vector<Datapoint> parse(const std::string& filename);
};

}

#endif // CSV_PARSER_HPP