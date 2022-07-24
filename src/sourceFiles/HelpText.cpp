/*
 * Editors: Sebastian Wolf, Tobias Goetz
 */

#include "headerFiles/HelpText.h"

HelpText::HelpText(GetOptSetup *getOptSetup)
{
    this->getOptSetup = getOptSetup;
}
HelpText::~HelpText() = default;

void HelpText::parseDescription()
{
    string new_description;

    for (int i = 0; i < getOptSetup->getOverAllDescriptions().size(); i++)
    {
        // Add empty space in front of every string except the first
        if (i > 0) {
            new_description.append(" ");
        }
        // concatenate strings
        new_description.append(getOptSetup->getOverAllDescriptions()[i]);
    }
    // justify and add to printHelpText
    printHelpText.append("Description:\\n" + justify.justifyTheText(new_description, getOptSetup->getSignPerLine(), false, 0) + "\\n");
}

bool compareOptions(const Option &a, const Option &b) {
    if (a.getShortOpt() != '\0' && b.getShortOpt() != '\0') {
        return a.getShortOpt() < b.getShortOpt();
    }
    else if (a.getShortOpt() != '\0') {
        return true;
    }
    else if (b.getShortOpt() != '\0') {
        return false;
    }
    else {
        return a.getLongOpt() < b.getLongOpt();
    }
}

vector<string> HelpText::concatParams(const vector<Option>& options)
{
    vector<string> opts;

    for (const auto & option : options) {
        string opt;
        // check if shortOpt isn't empty
        if (option.getShortOpt() != '\0')
        {
            // for e.g. -h
            opt += '-';
            opt += option.getShortOpt();
            // check if longOpt isn't empty
            if (!option.getLongOpt().empty())
            {
                // for e.g. , --help
                opt.append(", --" + option.getLongOpt());
            }
        }

            // check if only longOpt isn't empty
        else if (!option.getLongOpt().empty())
        {
            // for e.g. --help
            opt.append("--" + option.getLongOpt());
        }

        // Find out the longest parameter length
        if (opt.size() > maxOptionParamLength) {
            maxOptionParamLength = (int) opt.length();
        }
        opts.push_back(opt);
    }
    return opts;
}

void HelpText::parseOption()
{
    // sorting options
    vector<Option> sortedOpts = getOptSetup->getOptions();
    std::sort(sortedOpts.begin(), sortedOpts.end(), compareOptions);

    // concatenate params
    vector<string> opts = concatParams(sortedOpts);

    // concatenate the options
    std::stringstream buffer;
    buffer << std::left << std::setw(maxOptionParamLength + shift) << "Parameters";
    buffer << "Description" << "\\n";

    for (int i = 0; i < sortedOpts.size(); i++)
    {
        // get the concatenated params
        buffer << std::left << std::setw(maxOptionParamLength + shift) << opts[i];

        // check if description isn't empty
        if (!getOptSetup->getOptions()[i].getDescription().empty())
        {
            // subtract the length of the params and the shift
            // to get the new signPerLine for the options
            // needs to be less because of the Params and the shift
            int new_signPerLine = getOptSetup->getSignPerLine() - maxOptionParamLength - shift;
            // new shift for every description line after the first, to match the first line
            int optionShift = maxOptionParamLength + shift;

            // justify the description text
            string new_description = justify.justifyTheText(sortedOpts[i].getDescription(), new_signPerLine, true, optionShift);
            buffer << new_description;
        }
    }
    buffer << "\\n";
    printHelpText.append(buffer.str());
}

void HelpText::parseUsage()
{
    string new_usage;
    for (const auto & sampleUsage : getOptSetup->getSampleUsages()) {
        new_usage.append(sampleUsage + "\\n");
    }
    printHelpText.append("Usage:\\n" + justify.justifyTheText(new_usage, getOptSetup->getSignPerLine(), false, 0));
}

void HelpText::parseAuthor()
{
    printHelpText.append("Author:\\n" + justify.justifyTheText(getOptSetup->getAuthor().getName() + ", " + getOptSetup->getAuthor().getMail(), getOptSetup->getSignPerLine(), false, 0));
}

string HelpText::parseHelpMessage()
{
    // add function beginning to string
    printHelpText.append("void ");
    printHelpText.append(getOptSetup->getClassName());
    printHelpText.append("::printHelp(){puts(\"");

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
