/*
 * Editors: Tobias Goetz
 */

#include "models/headerFiles/Option.h"
#include <boost/lexical_cast.hpp>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <xercesc/util/XMLString.hpp>
#include <iostream>

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
    int _ref = boost::lexical_cast<int>(ref);
    if (_ref < 1 || _ref > 63) {
        std::cerr << "Error: Invalid ref value: [" << _ref << "]. Must be between 1 and 63." << std::endl;
        exit(EXIT_FAILURE);
    }
    Option::ref = _ref;
}

void Option::setShortOpt(const std::string &_shortOpt) {
    Option::shortOpt = boost::lexical_cast<char>(_shortOpt);
}

void Option::setLongOpt(const std::string &_longOpt) {
    Option::longOpt = _longOpt;
}

void Option::setDescription(const std::string &_description) {
    Option::description = _description;
}

void Option::setExclusions(const std::string &_exclusions) {
    std::vector<std::string> excls;
    boost::split(excls, _exclusions, boost::is_any_of(","));
    for (auto &excl : excls) {
        Option::exclusions.push_back(boost::lexical_cast<int>(excl));
    }
}

void Option::setConnectToInternalMethod(const std::string &_connectToInternalMethod) {
    Option::connectToInternalMethod = _connectToInternalMethod;
}

void Option::setConnectToExternalMethod(const std::string &_connectToExternalMethod) {
    Option::connectToExternalMethod = _connectToExternalMethod;
}

void Option::setHasArguments(const std::string &_hasArguments) {
    if (boost::iequals(_hasArguments, "optional")) {
        Option::hasArguments = HasArguments::OPTIONAL;
    } else if (boost::iequals(_hasArguments, "required")) {
        Option::hasArguments = HasArguments::REQUIRED;
    } else {
        throw std::runtime_error("Invalid value for hasArguments");
    }
}

void Option::setConvertTo(const std::string &_convertTo) {
    if (boost::iequals(_convertTo, "String")) {
        Option::convertTo = ConvertToOptions::STRING;
    } else if (boost::iequals(_convertTo, "Integer")) {
        Option::convertTo = ConvertToOptions::INTEGER;
    } else if (boost::iequals(_convertTo, "Boolean")) {
        Option::convertTo = ConvertToOptions::BOOLEAN;
    } else {
        throw std::runtime_error("Invalid value for convertTo");
    }
}

void Option::setDefaultValue(const std::string &_defaultValue) {
    Option::defaultValue = _defaultValue;
}

void Option::setInterface(const std::string &_interface) {
    Option::interface = _interface;
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
