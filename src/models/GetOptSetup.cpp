/*
 * Editors: Tobias Goetz
 */

#include <xercesc/util/XMLString.hpp>
#include <boost/lexical_cast.hpp>
#include "models/GetOptSetup.h"
#include "Logger.h"

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
void GetOptSetup::setSignPerLine(const string &_signPerLine) {
    GetOptSetup::signPerLine = boost::lexical_cast<int>(_signPerLine);
}

void GetOptSetup::setAuthor(const Author &_author) {
    GetOptSetup::author = _author;
}

void GetOptSetup::setHeaderFileName(const string &_headerFileName) {
    GetOptSetup::headerFileName = _headerFileName;
}

void GetOptSetup::setSourceFileName(const string &_sourceFileName) {
    GetOptSetup::sourceFileName = _sourceFileName;
}

void GetOptSetup::setNamespaceName(const string &_namespaceName) {
    GetOptSetup::namespaceName = _namespaceName;
}

void GetOptSetup::setClassName(const string &_className) {
    GetOptSetup::className = _className;
}

void GetOptSetup::setOverAllDescriptions(const vector<string> &_overAllDescriptions) {
    GetOptSetup::overAllDescriptions = _overAllDescriptions;
}

void GetOptSetup::setSampleUsages(const vector<string> &_sampleUsages) {
    GetOptSetup::sampleUsages = _sampleUsages;
}

void GetOptSetup::setOptions(const vector<Option> &_options) {
    GetOptSetup::options = _options;
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
    LOG_TRACE("Starting GetOptSetup-Attributes parse");
    for (unsigned int i = 0; i < attributes.getLength(); i++) {
        if (!XMLString::compareString(attributes.getName(i), u"SignPerLine")) {
            setSignPerLine(std::string(XMLString::transcode(attributes.getValue(i))));
        }
    }
    LOG_TRACE("Finished GetOptSetup-Attributes parse");
}
