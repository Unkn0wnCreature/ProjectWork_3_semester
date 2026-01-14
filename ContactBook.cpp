#include "ContactBook.h"
#include <algorithm>
#include <iostream>
using namespace std;
string specialNoneString = "None";

ContactBook::ContactBook(QList<Contact> contactBook){
    this->contactBook = contactBook;
}

ContactBook::ContactBook(const ContactBook& contact_book){
    contactBook = contact_book.contactBook;
}

ContactBook::~ContactBook(){}

bool ContactBook::addContact(const Contact& contact){
    contactBook.append(contact);
    return true;
}

QList<Contact> ContactBook::searchContact(QList<QString> criteriaList){
    QList<Contact> result;

    for (Contact& contact : contactBook){
        bool matches = true;
        if (!criteriaList[0].isEmpty() && !contact.findByFirstName(criteriaList[0])) {
            matches = false;
        }
        if (!criteriaList[1].isEmpty() && !contact.findBySecondName(criteriaList[1])) {
            matches = false;
        }
        if (!criteriaList[2].isEmpty() && !contact.findByLastName(criteriaList[2])) {
            matches = false;
        }
        if (!criteriaList[3].isEmpty() && !contact.findByBirthDate(criteriaList[3])) {
            matches = false;
        }
        if (!criteriaList[4].isEmpty() && !contact.findByAddress(criteriaList[4])) {
            matches = false;
        }
        if (!criteriaList[5].isEmpty() && !contact.findByEmail(criteriaList[5])) {
            matches = false;
        }
        if (!criteriaList[6].isEmpty() && !contact.findByPhoneNumber(criteriaList[6])) {
            matches = false;
        }
            
        if (matches) {
            result.append(contact);
        }
    }
    return result;
}

bool ContactBook::deleteContact(int index){
    if (index >= 0 && index < contactBook.size()){
        contactBook.removeAt(index);
        return true;
    }
    return false;
}


bool ContactBook::updateContact(int index, const Contact& contact){
    if (index >= 0 && index < contactBook.size()){
        contactBook[index] = contact;
        return true;
    }
    return false;
}

void ContactBook::saveContacts(){
    if (!fileStorage.saveToFile(contactBook)){cout<<"\nError: can't open file!\n"<<endl;}
}

void ContactBook::loadContacts(){
    contactBook = fileStorage.loadFromFile();
}

Contact ContactBook::getContact(int index) const
{
    if (index >= 0 && index < contactBook.size()){
        return contactBook[index];
    }
    return Contact();
}
