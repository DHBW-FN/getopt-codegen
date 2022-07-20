#include "HelpText.h"

HelpText::HelpText(GetOptSetup *getOptSetup)
{
    this->getOptSetup = getOptSetup;
}
HelpText::~HelpText() = default;

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
 * @brief concatenate the description strings to one string
 * @param description
 * @return all description strings as a string, space separated.
 */
string HelpText::parseDescription()
{
    string new_description;
    // Add empty space in front of every string
    for (int i = 0; i < getOptSetup->getOverAllDescriptions().size(); i++)
    {
        if (i > 0) {
            new_description.append(" ");
        }
        new_description.append(getOptSetup->getOverAllDescriptions()[i]);
    }

    // concatenate the strings into one string
    for (int i = 0; i < getOptSetup->getOverAllDescriptions().size(); i++)
    {
        new_description.append(getOptSetup->getOverAllDescriptions()[i]);
    }
    return new_description;
}

/**
 * @brief concatenate usage strings to one string
 * @param usage
 * @return all usage strings as a string with line break.
 */
string HelpText::parseUsage()
{
    string new_usage;

    for (int i = 0; i < getOptSetup->getSampleUsages().size(); i++) {
        new_usage.append(getOptSetup->getSampleUsages()[i]);

        // append line break at the end of usage string
        // except for the last one
        if (i < getOptSetup->getSampleUsages().size() - 1)
        {
            new_usage.append("\\n");
        }
    }

    return new_usage;
}

/**
 * @brief concatenate the author information to one string
 * @return information about author as a string.
 */
string HelpText::parseAuthor()
{
    string new_author;
    new_author.append(getOptSetup->getAuthor().getName() + ", " + getOptSetup->getAuthor().getMail());

    return new_author;
}

/**
 * @brief concatenate the options to one string
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
    buffer << std::left << std::setw(optionParamLength + shift) << "Arguments";
    buffer << "Description" << "\\n";

    for (int i = 0; i < getOptSetup->getOptions().size(); i++)
    {
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
    optionsText = buffer.str();
}

/**
 * @brief concatenate everything together
 * @return getHelp() Function with message as string
 */
string HelpText::parseHelpMessage()
{
    // add function beginning to string
    printHelpText.append("void printHelp(){puts(\"");

    // parse the description
    string buffer_description = parseDescription();
    buffer_description = justify.justifyTheText(buffer_description, getOptSetup->getSignPerLine(), false, 0);

    // add description to string
    printHelpText.append("Description:\\n");
    printHelpText.append(buffer_description + "\\n");

    // parse the option
    parseOption();

    // add option to string
    printHelpText.append(optionsText);

    // parse the usage
    string buffer_usage = parseUsage();
    buffer_usage = justify.justifyTheText(buffer_usage, getOptSetup->getSignPerLine(), false, 0);

    // add usage to string
    printHelpText.append("Usage:\\n");
    printHelpText.append(buffer_usage);

    // parse the author
    string buffer_author = parseAuthor();
    buffer_author = justify.justifyTheText(buffer_author, getOptSetup->getSignPerLine(), false, 0);

    // add author to string
    printHelpText.append("Author:\\n");
    printHelpText.append(buffer_author);

    // add function ending to string
    printHelpText.append(R"(");})");

    return printHelpText;
}
