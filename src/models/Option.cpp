#include "Option.h"
#include <boost/lexical_cast.hpp>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <xercesc/util/XMLString.hpp>

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

HasArguments Option::isHasArguments() const {
    return hasArguments;
}

ConvertToOptions Option::getConvertTo() const {
    return convertTo;
}

std::string Option::getDefaultValue() const {
    return defaultValue;
}

std::string Option::getInterface() const {
    return interface;
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

void Option::setExclusions(const std::string &exclusions) {
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

void Option::setHasArguments(const std::string &hasArguments) {
    if (boost::iequals(hasArguments, "optional")) {
        Option::hasArguments = HasArguments::OPTIONAL;
    } else if (boost::iequals(hasArguments, "required")) {
        Option::hasArguments = HasArguments::REQUIRED;
    } else {
        throw std::runtime_error("Invalid value for hasArguments");
    }
}

void Option::setConvertTo(const std::string &convertTo) {
    if (boost::iequals(convertTo, "String")) {
        Option::convertTo = ConvertToOptions::STRING;
    } else if (boost::iequals(convertTo, "Integer")) {
        Option::convertTo = ConvertToOptions::INTEGER;
    } else if (boost::iequals(convertTo, "Boolean")) {
        Option::convertTo = ConvertToOptions::BOOLEAN;
    } else {
        throw std::runtime_error("Invalid value for convertTo");
    }
}

void Option::setDefaultValue(const std::string &defaultValue) {
    Option::defaultValue = defaultValue;
}

void Option::setInterface(const std::string &interface) {
    Option::interface = interface;
}

// Helpers

void Option::parseAttributes(AttributeList &attributes) {
    for (unsigned int i = 0; i < attributes.getLength(); i++) {
        if (!XMLString::compareString(attributes.getName(i), u"Ref")) {
            setRef(std::string(XMLString::transcode(attributes.getValue(i))));
        } else if (!XMLString::compareString(attributes.getName(i), u"ShortOpt")) {
            setShortOpt(std::string(XMLString::transcode(attributes.getValue(i))));
        } else if (!XMLString::compareString(attributes.getName(i), u"LongOpt")) {
            setLongOpt(std::string(XMLString::transcode(attributes.getValue(i))));
        } else if (!XMLString::compareString(attributes.getName(i), u"Description")) {
            setDescription(std::string(XMLString::transcode(attributes.getValue(i))));
        } else if (!XMLString::compareString(attributes.getName(i), u"Exclusion")) {
            setExclusions(std::string(XMLString::transcode(attributes.getValue(i))));
        } else if (!XMLString::compareString(attributes.getName(i), u"ConnectToInternalMethod")) {
            setConnectToInternalMethod(std::string(XMLString::transcode(attributes.getValue(i))));
        } else if (!XMLString::compareString(attributes.getName(i), u"ConnectToExternalMethod")) {
            setConnectToExternalMethod(std::string(XMLString::transcode(attributes.getValue(i))));
        } else if (!XMLString::compareString(attributes.getName(i), u"HasArguments")) {
            setHasArguments(std::string(XMLString::transcode(attributes.getValue(i))));
        } else if (!XMLString::compareString(attributes.getName(i), u"ConvertTo")) {
            setConvertTo(std::string(XMLString::transcode(attributes.getValue(i))));
        } else if (!XMLString::compareString(attributes.getName(i), u"DefaultValue")) {
            setDefaultValue(std::string(XMLString::transcode(attributes.getValue(i))));
        } else if (!XMLString::compareString(attributes.getName(i), u"Interface")) {
            setInterface(std::string(XMLString::transcode(attributes.getValue(i))));
        }
    }
}
