#include "util.h"

#include <utility>
#include <algorithm>
#include <iterator>
#include <fstream>

const char* TSV_RESULT_FILE = "incidents_found.tsv";

namespace util {
    bool str_contains_lower(std::string str1, std::string str2){
      return str_tolower(std::move(str1)).find(str_tolower(std::move(str2))) != std::string::npos;
    }

    std::string str_tolower(std::string str) {
      std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return tolower(c);});
      return str;
    }

    void save_results(std::vector<std::string> data){
      std::ofstream output_file(TSV_RESULT_FILE);
      std::ostream_iterator<std::string> output_iterator(output_file, "\n");
      copy(data.begin(), data.end(), output_iterator);
    }
}
