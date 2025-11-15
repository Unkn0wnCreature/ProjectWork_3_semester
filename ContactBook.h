#pragma once
#include "Contact.h"
#include "FileStorage.h"
#include <vector>
#include <string>
using namespace std;

enum SearchCriteria{FIRST_NAME = 1, SECOND_NAME, LAST_NAME, BIRTH_DATE, ADDRESS, EMAIL, PHONE_NUMBER, ALL};

class ContactBook {
    private:
    list<Contact> contactBook;
    FileStorage fileStorage;
    public:
    ContactBook(list<Contact> contactBook = {});
    ContactBook(const ContactBook& contact_book);
    ~ContactBook();

    size_t get_size() const;

    void categoryInput(string category, string& inputString, string status = "compulsory");
    Contact createContactByInput();
    void showContacts();
    bool addContact(const Contact& contact);
    list<Contact> searchContact();
    void deleteContact();
    void updateContact();

    static bool compareByFirstName(const Contact& contact1, const Contact& contact2);
    static bool compareBySecondName(const Contact& contact1, const Contact& contact2);
    static bool compareByLastName(const Contact& contact1, const Contact& contact2);
    static bool compareByBirthDate(const Contact& contact1, const Contact& contact2);
    static bool compareByAddress(const Contact& contact1, const Contact& contact2);
    static bool compareByEmail(const Contact& contact1, const Contact& contact2);
    static bool compareByFirstNameDecr(const Contact& contact1, const Contact& contact2);
    static bool compareBySecondNameDecr(const Contact& contact1, const Contact& contact2);
    static bool compareByLastNameDecr(const Contact& contact1, const Contact& contact2);
    static bool compareByBirthDateDecr(const Contact& contact1, const Contact& contact2);
    static bool compareByAddressDecr(const Contact& contact1, const Contact& contact2);
    static bool compareByEmailDecr(const Contact& contact1, const Contact& contact2);

    void showSortMenu();
    void sortContacts();

    void saveContacts();
    void loadContacts(ContactBook& contactBook);
};
