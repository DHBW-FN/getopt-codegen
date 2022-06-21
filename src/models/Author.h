#ifndef CODEGENERATOR_AUTHOR_H
#define CODEGENERATOR_AUTHOR_H

#include <string>

using namespace std;

class Author {
public:
    // Constructors
    Author();

    // Getters
    const string &getName() const;
    const string &getPhone() const;
    const string &getEmail() const;

    // Setters
    void setName(const string &name);
    void setPhone(const string &phone);
    void setEmail(const string &email);

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
    string email;
};


#endif //CODEGENERATOR_AUTHOR_H
