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

/**
 * @brief Class to justify a string
 */
class Justify
{
private:
    /**
    * @brief Function to join the words with spaces spread evenly
    * @param words vector with separated words
    * @param start current line start
    * @param end iterator
    * @param num_spaces
    * @param isOption check if its an options string
    * @param curr_line current line string is in
    * @param optionShift shift that needs to be added to aline lines
    * @return justified text
    */
    static string JoinALineWithSpace(
            vector<string>& words,
            int start, int end,
            int num_spaces,
            bool isOption,
            int curr_line,
            int optionShift);
    /**
    * @brief Function that justify the words of sentence of length of line L
    * @param words vector with separated words
    * @param L length of sign per line
    * @param isOption check if its an options string
    * @param optionShift shift that needs to be added to aline lines
    * @return whole justified string
    */
    static vector<string> JustifyText(
            vector<string>& words,
            int L,
            bool isOption,
            int optionShift);
    /**
    * @brief separates a string in single words
    * @param str string to parse
    * @return vector with splitted words
    */
    static vector<string> splitWords(const string& str);

    /**
    * @brief Function to return justified text
    * @param result vector with justified strings
    * @return justified text in as a string
    */
    static string returnJustifiedText(vector<string>& result);

public:
    /**
    * @brief function to call the justification
    * @param str string to justify
    * @param L length of sign per line
    * @param isOption check if its an options string
    * @param optionShift shift that needs to be added to aline lines
    * @return justified text as a string
    */
    string justifyTheText(const string& str, int L, bool isOption, int optionShift);
};


#endif //CODEGENERATOR_JUSTIFY_H
