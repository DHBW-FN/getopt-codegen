#ifndef CODEGENERATOR_HELPTEXT_H
#define CODEGENERATOR_HELPTEXT_H

#include "Justify.h"
#include "models/GetOptSetup.h"
#include <iostream>
#include <vector>

using namespace std;

class HelpText
{
private:
    string printHelpText;
    string optionsText;
    int optionParamLength = 0;
    int shift = 5;
    Justify justify;
    GetOptSetup *getOptSetup;

public:
    HelpText(GetOptSetup *getOptSetup);
    ~HelpText();

    string parseHelpMessage();
    void parseDescription();
    void parseUsage();
    void parseAuthor();
    void parseOption();

    string concatParams(int i);
    void getLength();
};

#endif //CODEGENERATOR_HELPTEXT_H
