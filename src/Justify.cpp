#include "Justify.h"

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
string Justify::JoinALineWithSpace(
        vector<string>& words,
        int start, int end,
        int num_spaces,
        bool isOption,
        int curr_line,
        int optionShift)
{

    // Number of words in current line
    int num_words_curr_line
            = end - start + 1;

    // String to store the justified text
    string line;

    for (int i = start; i < end; i++) {

        line += words[i];
        --num_words_curr_line;

        // Count number of current space needed
        int num_curr_space
                = ceil((double)(num_spaces)
                       / num_words_curr_line);

        // Insert spaces in string line
        line.append(num_curr_space, ' ');

        // Delete the spaces inserted in line
        num_spaces -= num_curr_space;
    }

    // Insert word to string line
    if (!isOption || curr_line == 1)
    {
        line += words[end];
        line.append(num_spaces, ' ');
    }
    else if (curr_line > 1)
    {
        line += words[end];
        line.insert(0, optionShift, ' ');
    }


    // Return justified text
    return line;
}

/**
 * @brief Function that justify the words of sentence of length of line L
 * @param words vector with separated words
 * @param L length of sign per line
 * @param isOption check if its an options string
 * @param optionShift shift that needs to be added to aline lines
 * @return whole justified string
 */
vector<string> Justify::JustifyText(
        vector<string>& words,
        int L,
        bool isOption,
        int optionShift)
{

    int curr_line = 1;
    int curr_line_start = 0;
    int num_words_curr_line = 0;
    int curr_line_length = 0;

    // To store the justified text
    vector<string> result;

    // Traversing the words array
    for (int i = 0; i < words.size(); i++) {

        // curr_line_start is the first word
        // in the current line, and i is
        // used to identify the last word
        ++num_words_curr_line;

        int lookahead_line_length
                = curr_line_length
                  + (int)words[i].size()
                  + (num_words_curr_line - 1);

        // If by including the words length becomes L,
        // then that set of words is justified
        // and add the justified text to result
        if (lookahead_line_length == L) {

            // Justify the set of words
            string ans
                    = JoinALineWithSpace(
                            words,
                            curr_line_start,
                            i,
                            i - curr_line_start,
                            isOption,
                            curr_line,
                            optionShift);

            // Store the justified text in result
            result.emplace_back(ans);

            // Start the current line
            // with next index
            curr_line_start = i + 1;

            // num of words in the current line
            // and current line length set to 0
            num_words_curr_line = 0;
            curr_line_length = 0;
            curr_line += 1;
        }

            // If by including the words such that
            // length of words becomes greater than L,
            // then hat set is justified with
            // one less word and add the
            // justified text to result
        else if (lookahead_line_length > L) {

            // Justify the set of words
            string ans
                    = JoinALineWithSpace(
                            words,
                            curr_line_start,
                            i - 1,
                            L - curr_line_length,
                            isOption,
                            curr_line,
                            optionShift);

            // Store the justified text in result
            result.emplace_back(ans);

            // Current line set to current word
            curr_line_start = i;

            // Number of words set to 1
            num_words_curr_line = 1;

            // Current line length set
            // to current word length
            curr_line_length = (int)words[i].size();
            curr_line += 1;
        }

            // If length is less than L then,
            // add the word to current line length
        else {
            curr_line_length
                    += (int)words[i].size();
        }
    }

    // Last line is to be left-aligned
    if (num_words_curr_line > 0) {
        string line
                = JoinALineWithSpace(
                        words,
                        curr_line_start,
                        (int)words.size() - 1,
                        num_words_curr_line - 1,
                        isOption,
                        curr_line,
                        optionShift);

        line.append(
                L - curr_line_length
                - (num_words_curr_line - 1),
                ' ');

        // Insert the last line
        // left-aligned to result
        result.emplace_back(line);
    }

    // Return result
    return result;
}

/**
 * @brief separates a string in single words
 * @param str string to parse
 * @return vector with splitted words
 */
vector<string> Justify::splitWords(const string& str)
{

    vector<string> words;

    // Tokenizer separates string to words
    char_separator<char> sep(" ");
    tokenizer<boost::char_separator<char> > tok(str, sep);
    for (auto it=tok.begin(); it!=tok.end(); ++it)
    {
        // push words to vector
        words.push_back(*it);
    }

    // Return the vector of
    // words extracted from
    // string
    return words;
}

/**
 * @brief Function to return justified text
 * @param result vector with justified strings
 * @return justified text in as a string
 */
string Justify::returnJustifiedText(vector<string>& result)
{
    stringstream buffer;

    for (auto& it : result) {
        buffer << it << "\\n";
    }
    return buffer.str();
}

/**
 * @brief function to call the justification
 * @param str string to justify
 * @param L length of sign per line
 * @param isOption check if its an options string
 * @param optionShift shift that needs to be added to aline lines
 * @return justified text as a string
 */
string Justify::justifyTheText(const string& str, int L, bool isOption, int optionShift)
{

    vector<string> words;

    // Inserting words from
    // given string
    words = this->splitWords(str);

    // Function call to
    // justify the text
    vector<string> result
            = this->JustifyText(words, L, isOption, optionShift);

    // Return the justified
    // text
    return returnJustifiedText(result);
}