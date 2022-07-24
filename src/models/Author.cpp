/*
 * Editors: Tobias Goetz
 */

#include <xercesc/util/XMLString.hpp>
#include "models/Author.h"

//Constructor
Author::Author() = default;

//Getters
const string &Author::getName() const {
    return name;
}

const string &Author::getPhone() const {
    return phone;
}

const string &Author::getMail() const {
    return mail;
}


//Setters
void Author::setName(const string &_name) {
    Author::name = _name;
}

void Author::setPhone(const string &_phone) {
    Author::phone = _phone;
}

void Author::setMail(const string &_mail) {
    Author::mail = _mail;
}

//helper function to parse the Author-Tag
void Author::parseAttributes(AttributeList &attributes) {
    for (unsigned int i = 0; i < attributes.getLength(); i++) {
        if (!XMLString::compareString(attributes.getName(i), u"Name")) {
            setName(std::string(XMLString::transcode(attributes.getValue(i))));
        } else if (!XMLString::compareString(attributes.getName(i), u"Phone")) {
            setPhone(std::string(XMLString::transcode(attributes.getValue(i))));
        } else if (!XMLString::compareString(attributes.getName(i), u"Mail")) {
            setMail(std::string(XMLString::transcode(attributes.getValue(i))));
        }
    }
}
