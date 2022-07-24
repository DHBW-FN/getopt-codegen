/*
 * Editors: Tobias Goetz
 */

#include <xercesc/util/XMLString.hpp>
#include "Author.h"

//Constructor
Author::Author() = default;

//Getter
const string &Author::getName() const {
    return name;
}

//Getter
const string &Author::getPhone() const {
    return phone;
}

//Getter
const string &Author::getMail() const {
    return mail;
}


//Setter
void Author::setName(const string &_name) {
    Author::name = _name;
}

//Setter
void Author::setPhone(const string &_phone) {
    Author::phone = _phone;
}

//Setter
void Author::setMail(const string &_mail) {
    Author::mail = _mail;
}


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
