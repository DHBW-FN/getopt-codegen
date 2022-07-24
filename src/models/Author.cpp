/*
 * Editors: Tobias Goetz
 */

#include <xercesc/util/XMLString.hpp>
#include "Author.h"

/**
 * @brief Constructor
 */
Author::Author() = default;


/**
 * @brief Getter
 * @return name
 */
const string &Author::getName() const {
    return name;
}

/**
 * @brief Getter
 * @return phone
 */
const string &Author::getPhone() const {
    return phone;
}

/**
 * @brief Getter
 * @return mail
 */
const string &Author::getMail() const {
    return mail;
}


/**
 * @brief Setter
 * @param name names of authors
 */
void Author::setName(const string &_name) {
    Author::name = _name;
}

/**
 * @brief Setter
 * @param phone phone number of authors
 */
void Author::setPhone(const string &_phone) {
    Author::phone = _phone;
}

/**
 * @brief Setter
 * @param mail mail of authors
 */
void Author::setMail(const string &_mail) {
    Author::mail = _mail;
}


/**
 * @brief Parses the attributes of the xml-tag <author>
 * @param attributes attributes of the xml-tag <author>
 */
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
