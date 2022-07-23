#ifndef CODEGENERATOR_HELPTEXT_H
#define CODEGENERATOR_HELPTEXT_H

#include "Justify.h"
#include "models/GetOptSetup.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class HelpText
{
public:
    explicit HelpText(GetOptSetup *getOptSetup);
    ~HelpText();

    string parseHelpMessage();

private:
    void parseDescription();
    void parseUsage();
    void parseAuthor();
    void parseOption();
    vector<Option> parseOpts();
    static vector<Option> sortShortOpts(vector<Option> optsVector);
    static vector<Option> sortLongOpts(vector<Option> opts_vector);

    string concatParams(const vector<Option>& sortedOpts, int i);
    void getParamLength();
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
    int optionParamLength = 0;
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
