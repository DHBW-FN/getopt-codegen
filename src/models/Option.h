#ifndef PROGRAMMING_C_OPTION_H
#define PROGRAMMING_C_OPTION_H

#include <string>
#include <vector>

enum class ConvertToOptions {
    STRING,
    INTEGER,
    BOOLEAN
};

class Option {
public:
    // Constructor
    Option();

    // Getters
    int getRef() const;
    char getShortOpt() const;
    const std::string &getLongOpt() const;
    const std::string &getDescription() const;
    std::vector<int> getExclusions() const;
    const std::string &getConnectToInternalMethod() const;
    const std::string &getConnectToExternalMethod() const;
    bool isHasArguments() const;
    ConvertToOptions getConvertTo() const;

    // Setters
    void setRef(const std::string &ref);
    void setShortOpt(const std::string &shortOpt);
    void setLongOpt(const std::string &longOpt);
    void setDescription(const std::string &description);
    void setExclusions(std::string &exclusions);

    // TODO add remaining setters and conversions
    void setConnectToInternalMethod(const std::string &connectToInternalMethod);
    void setConnectToExternalMethod(const std::string &connectToExternalMethod);
    void setHasArguments(bool hasArguments);
    void setConvertTo(ConvertToOptions convertTo);

private:
    /**
     * @brief ref: Value between 0 and 63
     * Reference to the option.
     */
    int ref;
    /**
     * @brief shortOpt
     * Short option.
     * Example: -h
     */
    char shortOpt;
    /**
     * @brief longOpt
     * Long option.
     * Example: --help
     */
    std::string longOpt;
    /**
     * @brief description
     * Description of the option.
     */
    std::string description;
    /**
     * @brief exclusions
     * Exclusions of the option.
     * Example: -h, --help
     */
    std::vector<int> exclusions;
    /**
     * @brief connectToInternalMethod
     * Name of the method that will be called when the option is executed.
     * Example: "help"
     */
    std::string connectToInternalMethod;
    /**
     * @brief connectToExternalMethod
     * Name of the method that will be called when the option is executed.
     * Example: "help"
     */
    std::string connectToExternalMethod;
    /**
     * @brief hasArguments
     * True if the option has arguments.
     */
    bool hasArguments{};
    /**
     * @brief convertTo
     * Type the argument should be converted to.
     */
    ConvertToOptions convertTo = ConvertToOptions::STRING;
};


#endif //PROGRAMMING_C_OPTION_H
