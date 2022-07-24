/*
 * Editors: Tobias Goetz
 */

#ifndef CODEGENERATOR_AUTHOR_H
#define CODEGENERATOR_AUTHOR_H

#include <string>
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/sax/AttributeList.hpp>

XERCES_CPP_NAMESPACE_USE
using namespace std;

/**
 * @brief Class for the Author-Tag
 */
class Author {
public:
    /**
     * @brief Constructor for the Author-Tag
     */
    Author();

    /**
     * @brief Getter for name
     */
    const string &getName() const;

    /**
     * @brief Getter for phone
     */
    const string &getPhone() const;

    /**
     * @brief Getter for mail
     */
    const string &getMail() const;

    /**
     * @brief Setter for name
     * @param _name name of author
     */
    void setName(const string &name);

    /**
     * @brief Setter for phone
     * @param _phone phone number of author
     */
    void setPhone(const string &phone);

    /**
     * @brief Setter for mail
     * @param _mail mail of author
     */
    void setMail(const string &email);

    /**
     * @brief Function to parse the Author-Tag
     * @param attr AttributeList of the Author-Tag
     */
    void parseAttributes(AttributeList &attributes);

private:
    /**
     * @brief name
     * Name of the author.
     */
    string name;
    /**
     * @brief phone
     * Phone number of the author.
     */
    string phone;
    /**
     * @brief email
     * Email of the author.
     */
    string mail;
};


#endif //CODEGENERATOR_AUTHOR_H
