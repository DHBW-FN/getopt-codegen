/*
 * Editors: Sebastian Wolf
 */

#ifndef CODEGENERATOR_AUTHOR_H
#define CODEGENERATOR_AUTHOR_H

#include <string>
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/sax/AttributeList.hpp>

XERCES_CPP_NAMESPACE_USE
using namespace std;

class Author {
public:
    // Constructors
    Author();

    // Getters
    const string &getName() const;
    const string &getPhone() const;
    const string &getMail() const;

    // Setters
    void setName(const string &name);
    void setPhone(const string &phone);
    void setMail(const string &email);

    // Helpers
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
