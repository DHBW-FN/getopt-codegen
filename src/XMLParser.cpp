/*
 * Editors: Tobias Goetz
 */

#include <xercesc/parsers/SAXParser.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>

#include "XMLParser.h"
#include "Logger.h"

#include <iostream>

XERCES_CPP_NAMESPACE_USE
using namespace std;

XMLParser::XMLParser(const std::string &filename) {
    this->filename = filename;
}

void XMLParser::parse() {
    LOG_INFO("Starting parsing of file " + filename);
    try {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cerr << "Error during initialization! :\n"
             << message << "\n";
        XMLString::release(&message);
    }

    auto* parser = new SAXParser;

    int errorCount = {0};

    try
    {
        //Das eigentliche Parsen der Datei
        parser->setDocumentHandler(this);
        parser->parse(this->filename.c_str());
        errorCount = parser->getErrorCount();
    }
    catch (const OutOfMemoryException&)
    {
        XERCES_STD_QUALIFIER cerr << "OutOfMemoryException" << XERCES_STD_QUALIFIER endl;
    }
    catch (const XMLException& toCatch)
    {
        char* message = XMLString::transcode(toCatch.getMessage());

        cerr << "XMLException: " << message << endl;
    }
    catch(...) {
        cerr << "Unbekannter Fehler" << endl;
    }

    if (errorCount > 0) {
        perror("There were errors during parsing.");
        exit(1);
    }

    //Parser sauber beenden
    delete parser;
    //Terminate muss immer am Schluss stehen
    XMLPlatformUtils::Terminate();
    LOG_INFO("Finished parsing of file " + filename);
}

void XMLParser::startDocument() {
//    cout << "Start Document" << endl;
}

void XMLParser::endDocument() {
//    cout << "End Document" << endl;
}

void XMLParser::startElement(const XMLCh *const name, AttributeList &attributes) {
    if (!XMLString::compareString(name, u"GetOptSetup")) {
        sm->handleEvent(Event::GETOPTSETUPSTART);
        getOptSetup->parseAttributes(attributes);
    } else if (!XMLString::compareString(name, u"Author")) {
        sm->handleEvent(Event::AUTHORSTART);
        auto author = new Author();
        author->parseAttributes(attributes);
        getOptSetup->setAuthor(*author);
    } else if (!XMLString::compareString(name, u"HeaderFileName")) {
        sm->handleEvent(Event::HEADERFILENAMESTART);
    } else if (!XMLString::compareString(name, u"SourceFileName")) {
        sm->handleEvent(Event::SOURCEFILENAMESTART);
    } else if (!XMLString::compareString(name, u"NameSpace")) {
        sm->handleEvent(Event::NAMESPACESTART);
    } else if (!XMLString::compareString(name, u"ClassName")) {
        sm->handleEvent(Event::CLASSNAMESTART);
    } else if (!XMLString::compareString(name, u"OverAllDescription")) {
        sm->handleEvent(Event::OVERALLDESCRIPTIONSTART);
    } else if (!XMLString::compareString(name, u"Block")) {
        sm->handleEvent(Event::BLOCKSTART);
    } else if (!XMLString::compareString(name, u"SampleUsage")) {
        sm->handleEvent(Event::SAMPLEUSAGESTART);
    } else if (!XMLString::compareString(name, u"Sample")) {
        sm->handleEvent(Event::SAMPLESTART);
    } else if (!XMLString::compareString(name, u"Options")) {
        sm->handleEvent(Event::OPTIONSSTART);
    }  else if (!XMLString::compareString(name, u"Option")) {
        sm->handleEvent(Event::OPTIONSTART);
        auto option = new Option();
        option->parseAttributes(attributes);
        getOptSetup->addOption(*option);
    }
}

void XMLParser::endElement(const XMLCh *const name) {
    if (!XMLString::compareString(name, u"GetOptSetup")) {
        sm->handleEvent(Event::GETOPTSETUPEND);
    } else if (!XMLString::compareString(name, u"Author")) {
        sm->handleEvent(Event::AUTHOREND);
    } else if (!XMLString::compareString(name, u"HeaderFileName")) {
        sm->handleEvent(Event::HEADERFILENAMEEND);
    } else if (!XMLString::compareString(name, u"SourceFileName")) {
        sm->handleEvent(Event::SOURCEFILENAMEEND);
    } else if (!XMLString::compareString(name, u"NameSpace")) {
        sm->handleEvent(Event::NAMESPACEEND);
    } else if (!XMLString::compareString(name, u"ClassName")) {
        sm->handleEvent(Event::CLASSNAMEEND);
    } else if (!XMLString::compareString(name, u"OverAllDescription")) {
        sm->handleEvent(Event::OVERALLDESCRIPTIONEND);
    } else if (!XMLString::compareString(name, u"Block")) {
        sm->handleEvent(Event::BLOCKEND);
    } else if (!XMLString::compareString(name, u"SampleUsage")) {
        sm->handleEvent(Event::SAMPLEUSAGEEND);
    } else if (!XMLString::compareString(name, u"Sample")) {
        sm->handleEvent(Event::SAMPLEEND);
    } else if (!XMLString::compareString(name, u"Options")) {
        sm->handleEvent(Event::OPTIONSEND);
    }  else if (!XMLString::compareString(name, u"Option")) {
        sm->handleEvent(Event::OPTIONEND);
    }
}

void XMLParser::characters(const XMLCh *const chars, const XMLSize_t length) {
    switch (sm->getState()) {
        case State::START:
            break;
        case State::GETOPTSETUP:
            break;
        case State::AUTHOR:
            break;
        case State::HEADERFILENAME:
            getOptSetup->setHeaderFileName(std::string(XMLString::transcode(chars)));
            break;
        case State::SOURCEFILENAME:
            getOptSetup->setSourceFileName(std::string(XMLString::transcode(chars)));
            break;
        case State::NAMESPACE:
            getOptSetup->setNamespaceName(std::string(XMLString::transcode(chars)));
            break;
        case State::CLASSNAME:
            getOptSetup->setClassName(std::string(XMLString::transcode(chars)));
            break;
        case State::OVERALLDESCRIPTION:
            break;
        case State::BLOCK:
            getOptSetup->addOverAllDescription(std::string(XMLString::transcode(chars)));
            break;
        case State::SAMPLEUSAGE:
            break;
        case State::SAMPLE:
            getOptSetup->addSampleUsage(std::string(XMLString::transcode(chars)));
            break;
        case State::OPTIONS:
            break;
        case State::OPTION:
            break;
        case State::END:
            break;
    }
}

GetOptSetup *XMLParser::getGetOptSetup() const {
    return getOptSetup;
}

