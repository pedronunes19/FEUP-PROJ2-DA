#pragma once
#ifndef DA_PROJ_2_UTILS_H
#define DA_PROJ_2_UTILS_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <limits>


#define MAX_CHARS_IGNORE std::numeric_limits <std::streamsize>::max()

/**
 * @brief Exception thrown when the user wants to exit the program.
 */
class Exit {};

namespace utils::file {

    /**
     * @brief Clears the screen
     *
     */
    void clearScreen();

    /**
     * @brief Reads a file at the specified path and returns its content as a collection of its lines.
     * In the context of this project, and the dataset given (text files), the first line of each file.
     *
     * @param filePath the path of the file to read
     * @return a vector containing all the lines but the first of the given file
     */
    std::vector<std::string> readFile(const std::string& filePath);

    /**
     * @brief Splits a string by a character.
     *
     * @param str The string to be split.
     * @param sep The character to use as the separator.
     * @return A vector with all the words in the string that were separated by the
     *         given character.
     */
    std::vector<std::string> split(std::string str, char sep);

    /**
     * @brief Waits for the user to press ENTER
     *
     * @param prompt the prompt to show, defaults to "Press ENTER to continue..."
     */
    void waitForEnter(std::string prompt = "Press ENTER to continue...");

    /**
     * @brief Normalizes a string.
     *
     * @details Replaces all tabs with spaces, removes duplicate spaces and trims
     *          spaces from the start and the end.
     *
     * @param input The string to normalize.
     */
    void normalizeInput(std::string &input);
}

#endif //DA_PROJ_2_UTILS_H