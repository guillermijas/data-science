#ifndef DATA_SCIENCE_UTIL_H
#define DATA_SCIENCE_UTIL_H

#include <iostream>
#include <vector>


namespace util{
    bool str_contains_lower(std::string str1, std::string str2);
    std::string str_tolower(std::string str);
    void save_results(std::vector<std::string> data);
}

#endif
