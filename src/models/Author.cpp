//
// Created by tobig on 6/10/2022.
//

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

const string &Author::getEmail() const {
    return email;
}


// Setters
void Author::setName(const string &name) {
    Author::name = name;
}

void Author::setPhone(const string &phone) {
    Author::phone = phone;
}

void Author::setEmail(const string &email) {
    Author::email = email;
}


