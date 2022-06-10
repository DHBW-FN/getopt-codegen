#include "Option.h"

// Constructor
Option::Option() = default;

// Getters
int Option::getRef() const {
    return ref;
}

char *Option::getShortOpt() const {
    return shortOpt;
}

const std::string &Option::getLongOpt() const {
    return longOpt;
}

const std::string &Option::getDescription() const {
    return description;
}

int *Option::getExclusions() const {
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

void Option::setRef(int ref) {
    Option::ref = ref;
}

void Option::setShortOpt(char *shortOpt) {
    Option::shortOpt = shortOpt;
}

void Option::setLongOpt(const std::string &longOpt) {
    Option::longOpt = longOpt;
}

void Option::setDescription(const std::string &description) {
    Option::description = description;
}

void Option::setExclusions(int *exclusions) {
    Option::exclusions = exclusions;
}

void Option::setConnectToInternalMethod(const std::string &connectToInternalMethod) {
    Option::connectToInternalMethod = connectToInternalMethod;
}

void Option::setConnectToExternalMethod(const std::string &connectToExternalMethod) {
    Option::connectToExternalMethod = connectToExternalMethod;
}

void Option::setHasArguments(bool hasArguments) {
    Option::hasArguments = hasArguments;
}

void Option::setConvertTo(ConvertToOptions convertTo) {
    Option::convertTo = convertTo;
}