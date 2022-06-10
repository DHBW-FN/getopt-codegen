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
    string name;
    string phone;
    string email;
};


#endif //CODEGENERATOR_AUTHOR_H
