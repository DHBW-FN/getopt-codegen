#include "HelpText.h"

HelpText::HelpText(GetOptSetup *getOptSetup)
{
    this->getOptSetup = getOptSetup;
}
HelpText::~HelpText() = default;

/**
 * @brief concatenate the description strings to one string
 * @brief and add to printHelpText
 */
void HelpText::parseDescription()
{
    string new_description;

    // Add empty space in front of every string
    for (int i = 0; i < getOptSetup->getOverAllDescriptions().size(); i++)
    {
        if (i > 0) {
            new_description.append(" ");
        }
        // concatenate strings
        new_description.append(getOptSetup->getOverAllDescriptions()[i]);
    }
    // justify and add to printHelpText
    printHelpText.append("Description:\\n" + justify.justifyTheText(new_description, getOptSetup->getSignPerLine(), false, 0) + "\\n");
}

/**
 * @brief get the length of longest parameter in options
 * Calculate the length of the longest parameter in options.
 * Is used to know how much spacing should be used
 * to format the options parameters and description.
 */
void HelpText::getLength()
{
    int paramLength;

    for (int i = 0; i < getOptSetup->getOptions().size(); i++)
    {
        paramLength = 0;

        if (getOptSetup->getOptions()[i].getShortOpt() != '\0')
        {
            // for e. g. -h
            paramLength += 2;
        }

        // check if longOpt and shortOpt aren't empty
        if (!getOptSetup->getOptions()[i].getLongOpt().empty() && getOptSetup->getOptions()[i].getShortOpt() != '\0')
        {
            // for , --
            paramLength += 4;
            paramLength += (int)getOptSetup->getOptions()[i].getLongOpt().length();
        }

            // check if only longOpt isn't empty
        else if (!getOptSetup->getOptions()[i].getLongOpt().empty())
        {
            // for --
            paramLength += 2;
            paramLength += (int)getOptSetup->getOptions()[i].getLongOpt().length();
        }
    }

    if (paramLength > optionParamLength)
    {
        optionParamLength = paramLength;
    }
}


/**
 * @brief concatenate short opt and long opt to one string
 * @param i iteration counter to determine which option is parsed
 * @return concatenated opts as string
 * different checks if shortOpt and LongOpt are empty
 * to concatenate the right signs to the string
 */
string HelpText::concatParams(int i)
{
    string opts;

    if (getOptSetup->getOptions()[i].getShortOpt() != '\0')
    {
        // for e.g. -h
        opts += '-';
        opts += getOptSetup->getOptions()[i].getShortOpt();
    }

    // check if longOpt and shortOpt aren't empty
    if (!getOptSetup->getOptions()[i].getLongOpt().empty() && getOptSetup->getOptions()[i].getShortOpt() != '\0')
    {
        // for e.g. , --help
        opts.append(", --" + getOptSetup->getOptions()[i].getLongOpt());
    }

        // check if only longOpt isn't empty
    else if (!getOptSetup->getOptions()[i].getLongOpt().empty())
    {
        // for e.g. --help
        opts.append("--" + getOptSetup->getOptions()[i].getLongOpt());
    }

    return opts;
}

/**
 * @brief concatenate the options to one string
 * @brief and add to printHelpText
 * call the getLength() Method. Get concatenated params
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
void HelpText::parseOption()
{
    // calculate the length of the longest param
    getLength();

    // concatenate the options
    std::stringstream buffer;
    buffer << std::left << std::setw(optionParamLength + shift) << "Parameters";
    buffer << "Description" << "\\n";

    for (int i = 0; i < getOptSetup->getOptions().size(); i++)
    {
        // get the concatenated params
        string opts = concatParams(i);
        buffer << std::left << std::setw(optionParamLength + shift) << opts;

        // check if description isn't empty
        if (!getOptSetup->getOptions()[i].getDescription().empty())
        {
            // subtract the length of the params and the shift
            // to get the new signPerLine for the options
            // needs to be less because of the Params and the shift
            int new_signPerLine = getOptSetup->getSignPerLine() - optionParamLength - shift;
            // new shift for every description line after the first, to match the first line
            int optionShift = optionParamLength + shift;

            // justify the description text
            string new_description = justify.justifyTheText(getOptSetup->getOptions()[i].getDescription(), new_signPerLine, true, optionShift);
            buffer << new_description;
        }
    }
    buffer << "\\n";
    printHelpText.append(buffer.str());
}

/**
 * @brief concatenate usage strings to one string
 * @brief and add to printHelpText
 * @return all usage strings as a string with line break.
 */
void HelpText::parseUsage()
{
    string new_usage;
    for (int i = 0; i < getOptSetup->getSampleUsages().size(); i++) {
        new_usage.append(getOptSetup->getSampleUsages()[i] + "\\n");
    }
    printHelpText.append("Usage:\\n" + justify.justifyTheText(new_usage, getOptSetup->getSignPerLine(), false, 0));
}

/**
 * @brief concatenate the author information to one string
 * @brief and add to printHelpText
 */
void HelpText::parseAuthor()
{
    printHelpText.append("Author:\\n" + justify.justifyTheText(getOptSetup->getAuthor().getName() + ", " + getOptSetup->getAuthor().getMail(), getOptSetup->getSignPerLine(), false, 0));
}

/**
 * @brief add function wrapper and call parse methods
 * @return getHelp() Function with message as string
 */
string HelpText::parseHelpMessage()
{
    // add function beginning to string
    printHelpText.append("void printHelp(){puts(\"");

    // parse the description and add text to string
    parseDescription();

    // parse the option and add text to string
    parseOption();

    // parse the usage and add text to string
    parseUsage();

    // parse the author and add text to string
    parseAuthor();

    // add function ending to string
    printHelpText.append(R"(");})");

    return printHelpText;
}
