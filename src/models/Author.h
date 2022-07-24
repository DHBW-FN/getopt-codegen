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

    /** @name Getter
    * @brief  Getter for the class
    */
    ///@{
    const string &getName() const;
    const string &getPhone() const;
    const string &getMail() const;
    ///@}

    /** @name Setter
    * @brief  Setter for the class
    */
    ///@{
    void setName(const string &name);
    void setPhone(const string &phone);
    void setMail(const string &email);
    ///@}

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
