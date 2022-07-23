/*
 * Editors: Tobias Goetz
 */

#include <xercesc/sax/HandlerBase.hpp>
XERCES_CPP_NAMESPACE_USE

#ifndef PROGRAMMING_C_XMLPARSER_H
#define PROGRAMMING_C_XMLPARSER_H


#include <string>
#include <codecvt>
#include <locale>
#include "StateMachine.h"
#include "models/GetOptSetup.h"

using namespace std;

class XMLParser : public HandlerBase {
private:
    /**
     * @brief filename
     * Name of the file to parse.
     */
    std::string filename;

    StateMachine *sm = new StateMachine();

    GetOptSetup *getOptSetup = new GetOptSetup();

    wstring_convert<codecvt_utf8_utf16<char16_t>,char16_t> converter;
public:
    /**
     * @brief XMLParser
     * Constructor.
     * @param filename
     */
    explicit XMLParser(const string &filename);

    void parse();

    void startDocument() override;
    void endDocument() override;
    void startElement(const XMLCh* name, AttributeList& attributes) override;
    void endElement(const XMLCh* name) override;
    void characters(const XMLCh* chars, XMLSize_t length) override;

    /**
     * @brief getGetOptSetup
     * @return
     */
    GetOptSetup *getGetOptSetup() const;
};


#endif //PROGRAMMING_C_XMLPARSER_H
