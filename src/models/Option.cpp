#include "Option.h"
#include <boost/lexical_cast.hpp>
#include <vector>
#include <boost/algorithm/string.hpp>

// Constructor
Option::Option() = default;

// Getters
int Option::getRef() const {
    return ref;
}

char Option::getShortOpt() const {
    return shortOpt;
}

const std::string &Option::getLongOpt() const {
    return longOpt;
}

const std::string &Option::getDescription() const {
    return description;
}

std::vector<int> Option::getExclusions() const {
    return exclusions;
}

const std::string &Option::getConnectToInternalMethod() const {
    return connectToInternalMethod;
}

const std::string &Option::getConnectToExternalMethod() const {
    return connectToExternalMethod;
}

bool Option::isHasArguments() const {
    return hasArguments;
}

ConvertToOptions Option::getConvertTo() const {
    return convertTo;
}


// Setters

void Option::setRef(const std::string &ref) {
    Option::ref = boost::lexical_cast<int>(ref);
}

void Option::setShortOpt(const std::string &shortOpt) {
    Option::shortOpt = boost::lexical_cast<char>(shortOpt);
}

void Option::setLongOpt(const std::string &longOpt) {
    Option::longOpt = longOpt;
}

void Option::setDescription(const std::string &description) {
    Option::description = description;
}

void Option::setExclusions(std::string &exclusions) {
    std::vector<std::string> excl;
    boost::split(excl, exclusions, boost::is_any_of(","));
    for (auto &excl : excl) {
        Option::exclusions.push_back(boost::lexical_cast<int>(excl));
    }
}

void Option::setConnectToInternalMethod(const std::string &connectToInternalMethod) {
    Option::connectToInternalMethod = connectToInternalMethod;
}

void Option::setConnectToExternalMethod(const std::string &connectToExternalMethod) {
    Option::connectToExternalMethod = connectToExternalMethod;
}

void Option::setHasArguments(std::string &hasArguments) {
    if (boost::iequals(hasArguments, "optional")) {
        Option::hasArguments = HasArguments::OPTIONAL;
    } else if (boost::iequals(hasArguments, "required")) {
        Option::hasArguments = HasArguments::REQUIRED;
    } else {
        throw std::runtime_error("Invalid value for hasArguments");
    }
}

void Option::setConvertTo(std::string &convertTo) {
    if (boost::iequals(convertTo, "string")) {
        Option::convertTo = ConvertToOptions::STRING;
    } else if (boost::iequals(convertTo, "int")) {
        Option::convertTo = ConvertToOptions::INTEGER;
    } else if (boost::iequals(convertTo, "bool")) {
        Option::convertTo = ConvertToOptions::BOOLEAN;
    } else {
        throw std::runtime_error("Invalid value for convertTo");
    }
}