#include <xercesc/util/XMLString.hpp>
#include <boost/lexical_cast.hpp>
#include "GetOptSetup.h"

// Constructors
GetOptSetup::GetOptSetup() = default;


// Getters
const int &GetOptSetup::getSignPerLine() const {
    return signPerLine;
}

const Author &GetOptSetup::getAuthor() const {
    return author;
}

const string &GetOptSetup::getHeaderFileName() const {
    return headerFileName;
}

const string &GetOptSetup::getSourceFileName() const {
    return sourceFileName;
}

const string &GetOptSetup::getNamespaceName() const {
    return namespaceName;
}

const string &GetOptSetup::getClassName() const {
    return className;
}

const vector<string> &GetOptSetup::getOverAllDescriptions() const {
    return overAllDescriptions;
}

const vector<string> &GetOptSetup::getSampleUsages() const {
    return sampleUsages;
}

const vector<Option> &GetOptSetup::getOptions() const {
    return options;
}


// Setters
void GetOptSetup::setSignPerLine(const string &signPerLine) {
    GetOptSetup::signPerLine = boost::lexical_cast<int>(signPerLine);
}

void GetOptSetup::setAuthor(const Author &author) {
    GetOptSetup::author = author;
}

void GetOptSetup::setHeaderFileName(const string &headerFileName) {
    GetOptSetup::headerFileName = headerFileName;
}

void GetOptSetup::setSourceFileName(const string &sourceFileName) {
    GetOptSetup::sourceFileName = sourceFileName;
}

void GetOptSetup::setNamespaceName(const string &namespaceName) {
    GetOptSetup::namespaceName = namespaceName;
}

void GetOptSetup::setClassName(const string &className) {
    GetOptSetup::className = className;
}

void GetOptSetup::setOverAllDescriptions(const vector<string> &overAllDescriptions) {
    GetOptSetup::overAllDescriptions = overAllDescriptions;
}

void GetOptSetup::setSampleUsages(const vector<string> &sampleUsages) {
    GetOptSetup::sampleUsages = sampleUsages;
}

void GetOptSetup::setOptions(const vector<Option> &options) {
    GetOptSetup::options = options;
}

// Adders
void GetOptSetup::addOverAllDescription(const string &overAllDescription) {
    GetOptSetup::overAllDescriptions.push_back(overAllDescription);
}

void GetOptSetup::addSampleUsage(const string &sampleUsage) {
    GetOptSetup::sampleUsages.push_back(sampleUsage);
}

void GetOptSetup::addOption(const Option &option) {
    GetOptSetup::options.push_back(option);
}

// Helpers
void GetOptSetup::parseAttributes(AttributeList &attributes) {
    for (unsigned int i = 0; i < attributes.getLength(); i++) {
        if (!XMLString::compareString(attributes.getName(i), u"SignPerLine")) {
            setSignPerLine(std::string(XMLString::transcode(attributes.getValue(i))));
        }
    }
}
