#include <xercesc/parsers/SAXParser.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>

#include "XMLParser.h"

#include <iostream>

XERCES_CPP_NAMESPACE_USE
using namespace std;

std::string XMLParser::toString() {
    return this->filename;
}

XMLParser::XMLParser(const std::string &filename) {
    this->filename = filename;
}

void XMLParser::parse() {
    try {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cerr << "Error during initialization! :\n"
             << message << "\n";
        XMLString::release(&message);
    }

    SAXParser* parser = {nullptr};
    parser = new SAXParser;

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

        //XMLString::release(message);
        /*
        XERCES_STD_QUALIFIER cerr << "\nAn error occurred\n  Error: "
                                  << StrX(toCatch.getMessage())
                                  << "\n" << XERCES_STD_QUALIFIER endl;
                                  */
        cerr << "XMLException: " << message << endl;
    }
    catch(...) {
        cerr << "Unbekannter Fehler" << endl;
    }

    cout << "Anzahl Fehler: " << errorCount << endl;

    //Parser sauber beenden
    delete parser;
    //Terminate muss immer am Schluss stehen
    XMLPlatformUtils::Terminate();
}

void XMLParser::startDocument() {
    cout << "Start Document" << endl;
    sm.setState(State::START);
}

void XMLParser::endDocument() {
    cout << "End Document" << endl;
}

void XMLParser::startElement(const XMLCh *const name, AttributeList &attributes) {
    cout << "Start-Element: " << converter.to_bytes(name) << endl;
}

void XMLParser::endElement(const XMLCh *const name) {
    cout << "End-Element: " << converter.to_bytes(name) << endl;
}

void XMLParser::characters(const XMLCh *const chars, const XMLSize_t length) {
    cout << "Characters (" << length << "):" << converter.to_bytes(chars, chars + length) << endl;
}

