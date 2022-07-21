#ifndef PROGRAMMING_C_OPTION_H
#define PROGRAMMING_C_OPTION_H

#include <string>
#include <vector>
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/sax/AttributeList.hpp>

XERCES_CPP_NAMESPACE_USE

enum class ConvertToOptions {
    STRING,
    INTEGER,
    BOOLEAN
};

enum class HasArguments {
    None,
    OPTIONAL,
    REQUIRED
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
    HasArguments isHasArguments() const;
    ConvertToOptions getConvertTo() const;
    std::string getDefaultValue() const;
    std::string getInterface() const;

    // Setters
    void setRef(const std::string &ref);
    void setShortOpt(const std::string &shortOpt);
    void setLongOpt(const std::string &longOpt);
    void setDescription(const std::string &description);
    void setExclusions(const std::string &exclusions);
    void setConnectToInternalMethod(const std::string &connectToInternalMethod);
    void setConnectToExternalMethod(const std::string &connectToExternalMethod);
    void setHasArguments(const std::string &hasArguments);
    void setConvertTo(const std::string &convertTo);
    void setDefaultValue(const std::string &defaultValue);
    void setInterface(const std::string &interface);

    // Helpers
    char* toString();
    void parseAttributes(AttributeList &attributes);
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
    HasArguments hasArguments{};
    /**
     * @brief convertTo
     * Type the argument should be converted to.
     */
    ConvertToOptions convertTo = ConvertToOptions::STRING;
    /**
     * @brief defaultValue
     * Default value of the option.
     */
    std::string defaultValue;
    /**
     * @brief interface
     * Interface of the option.
     */
    std::string interface;
};


#endif //PROGRAMMING_C_OPTION_H
