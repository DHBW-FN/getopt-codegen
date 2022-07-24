/*
 * Editors: Tobias Goetz
 */

#ifndef PROGRAMMING_C_CODEGENERATOR_H
#define PROGRAMMING_C_CODEGENERATOR_H

#include <string>

/**
 * @brief Class for the CodeGenerator
 */
class CodeGenerator {
private:
    /**
     * @brief String containing path to the file
     */
    std::string filePath;

    /**
     * @brief Output directory
     */
    std::string outputDir;

public:
    /**
     * @brief Constructor
     */
    CodeGenerator() = default;

    /**
     * @brief Get the path to the file
     * @return
     */
    std::string getFilePath();

    /**
     * Get the output directory
     * @return the out directory as string
     */
    std::string getOutputDir();

    /**
     * @brief Set the path to the file
     * @param filename
     */
    void setFilePath(const std::string &filename);

    /**
     * @brief Set the output directory
     * @param dir
     */
    void setOutputDir(const std::string &dir);

    /**
     * @brief Runs the CodeGenerator
     */
    void run();
};


#endif //PROGRAMMING_C_CODEGENERATOR_H
