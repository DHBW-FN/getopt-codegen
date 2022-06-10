#include "XMLParser.h"

std::string XMLParser::toString() {
    return this->filename;
}

XMLParser::XMLParser(std::string filename) {
    this->filename = filename;
}
