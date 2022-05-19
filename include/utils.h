#include <string>
#include <vector>

#ifndef DA_PROJ_2_UTILS_H
#define DA_PROJ_2_UTILS_H

namespace utils::file {

    /**
     * @brief Reads a file at the specified path and returns its content as a collection of its lines.
     * In the context of this project, and the dataset given (text files), the first line of each file.
     *
     * @param filePath the path of the file to read
     * @return a vector containing all the lines but the first of the given file
     */
    std::vector<std::string> readFile(const std::string& filePath);
}

#endif //DA_PROJ_2_UTILS_H