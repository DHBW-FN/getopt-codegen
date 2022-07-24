/*
 * Editors: Sebastian Wolf, Tobias Goetz
 */

#ifndef CODEGENERATOR_HELPTEXT_H
#define CODEGENERATOR_HELPTEXT_H

#include "Justify.h"
#include "models/headerFiles/GetOptSetup.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * @brief Class for the HelpText parsing
 */
class HelpText
{
public:
    /**
     * @brief Constructor for the HelpText
     */
    explicit HelpText(GetOptSetup *getOptSetup);
    /**
     * @brief Destructor for the HelpText
     */
    ~HelpText();

    /**
    * @brief add function wrapper and call parse methods
    * @return getHelp() Function with message as string
    */
    string parseHelpMessage();

private:
    /**
    * @brief concatenate the description strings to one string
    * @brief and add to printHelpText
    */
    void parseDescription();

    /**
    * @brief concatenate usage strings to one string
    * @brief and add to printHelpText
    * @return all usage strings as a string with line break.
    */
    void parseUsage();

    /**
    * @brief concatenate the author information to one string
    * @brief and add to printHelpText
    */
    void parseAuthor();

    /**
    * @brief concatenate the options to one string
    * @brief and add to printHelpText
    * call the getMaxParamLength() Method. Get concatenated params
    * by calling concatParams function with i as iterator.
    * write strings to buffer with a spacing using set()
    * calculate a new signPerLine to space out the
    * option description accordingly to the length
    * of param and the shift.
    * calculate a new shift for every line of the description
    * that is pushed to the next line because of signPerLine,
    * in order to shift the line to the right, matching the above.
    * Justify the description text. Write justified text to
    * class variable.
    */
    void parseOption();

    /**
    * @brief concatenate short opt and long opt to one string
    * different checks if shortOpt and LongOpt are empty
    * to concatenate the right signs to the string
    * @param i iteration counter to determine which option is parsed
    * @return concatenated opts as string
    */
    vector<string> concatParams(const vector<Option>& sortedOpts);
    /**
     * @brief printHelp Text
     * stores the string for the printHelp method.
     */
    string printHelpText;
    /**
     * @brief Length of longest Parameter
     * Stores the length of the longest
     * parameter in options.
     */
    int maxOptionParamLength = 0;
    /**
     * @brief shift
     * extra shift / space can be defined
     * for the space between parameters
     * and description in options.
     */
    const int shift = 5;
    /**
     * @brief Justify object
     */
    Justify justify;
    /**
     * @brief GetOptSetup object
     */
    GetOptSetup *getOptSetup;
};

#endif //CODEGENERATOR_HELPTEXT_H
