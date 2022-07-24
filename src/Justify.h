/*
 * Editors: Sebastian Wolf
 */

#ifndef CODEGENERATOR_JUSTIFY_H
#define CODEGENERATOR_JUSTIFY_H
#include "bits/stdc++.h"
#include <iostream>
#include <boost/tokenizer.hpp>
#include <string>

using namespace std;
using namespace boost;

class Justify
{
private:
    static string JoinALineWithSpace(
            vector<string>& words,
            int start, int end,
            int num_spaces,
            bool isOption,
            int curr_line,
            int optionShift);

    static vector<string> JustifyText(
            vector<string>& words,
            int L,
            bool isOption,
            int optionShift);

    static vector<string> splitWords(const string& str);

    static string returnJustifiedText(vector<string>& result);

public:
    string justifyTheText(const string& str, int L, bool isOption, int optionShift);
};


#endif //CODEGENERATOR_JUSTIFY_H
