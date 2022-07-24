/*
 * Editors: Tobias Goetz
 */

#ifndef PROGRAMMING_C_CODEGENERATOR_H
#define PROGRAMMING_C_CODEGENERATOR_H

#include <string>

/**
 * @brief Class of CodeGenerator
 */
class CodeGenerator {
private:
    /**
     * @brief String containing path to the file
     */
    std::string filePath;

public:
    /**
     * @brief Constructor
     */
    CodeGenerator() = default;

    /**
     * @brief Set the path to the file
     * @param filename
     */
    void setFilePath(const std::string &filename);

    /**
     * @brief Get the path to the file
     * @return
     */
    std::string getFilePath();

    /**
     * @brief Runs the CodeGenerator
     */
    void run();
};


#endif //PROGRAMMING_C_CODEGENERATOR_H
