//
// Created by tobig on 6/10/2022.
//

#include <xercesc/util/XMLString.hpp>
#include "Author.h"

// Constructors
Author::Author() = default;


// Getters
const string &Author::getName() const {
    return name;
}

const string &Author::getPhone() const {
    return phone;
}

const string &Author::getMail() const {
    return mail;
}


// Setters
void Author::setName(const string &name) {
    Author::name = name;
}

void Author::setPhone(const string &phone) {
    Author::phone = phone;
}

void Author::setMail(const string &mail) {
    Author::mail = mail;
}


// Helpers
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
