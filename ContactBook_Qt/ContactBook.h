#pragma once
#include "Contact.h"
#include "FileStorage.h"
#include <QString>
#include <QList>
using namespace std;

class ContactBook {
    private:
    QList<Contact> contactBook;
    FileStorage fileStorage;
    public:
    ContactBook(QList<Contact> contactBook = {});
    ContactBook(const ContactBook& contact_book);
    ~ContactBook();

    Contact createContactByInput();
    void showContacts();
    bool addContact(const Contact& contact);
    QList<Contact> searchContact(QList<QString> criteriaList);
    bool deleteContact(int index);
    bool updateContact(int index, const Contact& contact);

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
    void loadContacts();

    QList<Contact> getContacts() const {return contactBook;}
    void setContacts(const QList<Contact>& contacts){contactBook = contacts;}
    Contact getContact(int index) const;

    void clearContacts(){contactBook.clear();}
};
