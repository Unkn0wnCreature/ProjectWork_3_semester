#include "ContactBook.h"
#include <algorithm>
#include <iostream>
using namespace std;
string specialNoneString = "None";

ContactBook::ContactBook(list<Contact> contactBook){
    this->contactBook = contactBook;
}

ContactBook::ContactBook(const ContactBook& contact_book){
    contactBook = contact_book.contactBook;
}

ContactBook::~ContactBook(){};

size_t ContactBook::get_size() const {return contactBook.size();}

void ContactBook::categoryInput(string category, string& inputString, string status){
    cout<<"Enter "<< category <<" ("<< status <<"):"<<endl;
    getline(cin, inputString);
}

Contact ContactBook::createContactByInput(){
    Contact contact;
    string firstName, secondName, lastName, birthDate, address, email, phone_number;

    categoryInput("first name", firstName);
    while (firstName.empty()){categoryInput("first name", firstName);}
    while (!contact.isValidName(firstName)){categoryInput("first name", firstName);}
    if (!contact.set_firstName(firstName)){cout<<"Ошибка присвоения имени."<<endl;}


    categoryInput("second name", secondName);
    while (secondName.empty()){categoryInput("second name", secondName);}
    while (!contact.isValidName(secondName)){categoryInput("second name", secondName);}
    if (!contact.set_secondName(secondName)){cout<<"Ошибка присвоения фамилии."<<endl;}

    categoryInput("last name", lastName, "optional");
    while (!contact.isValidName(lastName)){categoryInput("last name", lastName, "optional");}
    if (!contact.set_lastName(lastName)){cout<<"Ошибка присвоения отчества."<<endl;}

    categoryInput("birth date", birthDate, "optional");
    while (!contact.isValidDate(birthDate)){categoryInput("birth date", birthDate, "optional");}
    if (!contact.set_birthDate(birthDate)){cout<<"Ошибка присвоения даты рождения."<<endl;}

    categoryInput("address", address, "optional");
    while (!contact.isValidAddress(address)){categoryInput("address", address, "optional");}
    if (!contact.set_address(address)){cout<<"Ошибка присвоения даты адреса."<<endl;}

    categoryInput("email", email);
    while (email.empty()){categoryInput("email", email);}
    while (!contact.isValidEmail(email)){categoryInput("email", email);}
    if (!contact.set_email(email)){cout<<"Ошибка присвоения email."<<endl;}

    categoryInput("phone number", phone_number);
    while (phone_number.empty()){categoryInput("phone number", phone_number);}
    while (!contact.isValidPhone(phone_number)){categoryInput("phone number", phone_number);}
    if (!contact.addPhoneNumber(phone_number)){cout<<"Ошибка присвоения номера телефона."<<endl;}

    categoryInput("phone number", phone_number, "keep empty to stop adding phone numbers");
    while (!phone_number.empty()){
        while (!contact.isValidPhone(phone_number)){categoryInput("phone number", phone_number);}
        if (!contact.addPhoneNumber(phone_number)){cout<<"Ошибка присвоения фамилии."<<endl;}
        categoryInput("phone number", phone_number, "keep empty to stop adding phone numbers");
    }

    return contact;
}

void ContactBook::showContacts(){
    cout<<"\n-------L I S T    O F   C O N T A C T S-------\n"<<endl;
    for (Contact contact : contactBook){
        contact.show();
        cout<<"++++++++++++++++++++++++++++++++++++++++++"<<endl;
    }
}

bool ContactBook::addContact(const Contact& contact){
    contactBook.push_back(contact);
    return true;
}

list<Contact> ContactBook::searchContact(){
    list<Contact> result;
    string find_parameters[8];
    string parametres[7] = {"first name", "second name", "last name", "birth date", "address", "email", "phone number"};
    char status;
    
    cout<<"\nDo you want find through all fields? (y/n)"<<endl;
    cin>>status;
    cin.ignore();
    if (status == 'y' || status == 'Y'){
        categoryInput("string to find", find_parameters[7], "optional");
        for (Contact& contact : contactBook){
            if ((contact).findByString(find_parameters[7])){
                result.push_back(contact);
            }
        }
    } else {
        for (int i = 0; i < 7; i++){
            categoryInput(parametres[i], find_parameters[i], "optional");
        }

        for (Contact& contact : contactBook){
            bool matches = true;
            if (!find_parameters[0].empty() && !contact.findByFirstName(find_parameters[0])) {
                matches = false;
            }
            if (!find_parameters[1].empty() && !contact.findBySecondName(find_parameters[1])) {
                matches = false;
            }
            if (!find_parameters[2].empty() && !contact.findByLastName(find_parameters[2])) {
                matches = false;
            }
            if (!find_parameters[3].empty() && !contact.findByBirthDate(find_parameters[3])) {
                matches = false;
            }
            if (!find_parameters[4].empty() && !contact.findByAddress(find_parameters[4])) {
                matches = false;
            }
            if (!find_parameters[5].empty() && !contact.findByEmail(find_parameters[5])) {
                matches = false;
            }
            if (!find_parameters[6].empty() && !contact.findByPhoneNumber(find_parameters[6])) {
                matches = false;
            }
            
            if (matches) {
                result.push_back(contact);
            }
        }
    }
    cout<<"Found "<< result.size() <<" contact(s).\n"<<endl;
    return result;
}

void ContactBook::deleteContact(){
    list<Contact> list_to_delete = searchContact();
    char delete_all_status, status;

    cout<<"Want to delete all? (y/n)"<<endl;
        cin>>delete_all_status;
        cin.ignore();
    if (delete_all_status == 'y' || delete_all_status == 'Y'){
        for (Contact& contact_to_delete : list_to_delete) {
            for (auto it = contactBook.begin(); it != contactBook.end(); ) {
                if (*it == contact_to_delete) {
                    it = contactBook.erase(it);
                    cout << "Contact deleted." << endl;
                    break;
                } else {
                    ++it;
                }
            }
        }
    }else {
        for (Contact& contact_to_delete : list_to_delete) {
            contact_to_delete.show();
            
            char status;
            cout << "\nWant to delete this contact? (y/n)" << endl;
            cin >> status;
            cin.ignore();
            
            if (status == 'y' || status == 'Y'){
                // Находим и удаляем конкретный контакт
                for (auto it = contactBook.begin(); it != contactBook.end(); ) {
                    if (*it == contact_to_delete) {
                        it = contactBook.erase(it);
                        cout << "Contact deleted." << endl;
                        break;
                    } else {
                        ++it;
                    }
                }
            }
        }
    }
}

void ContactBook::updateContact(){
    list<Contact> list_to_update = searchContact();
    char global_status, status;

    cout<<"Want to update contacts? (y/n)"<<endl;
    cin>>global_status;
    cin.ignore();

    if (global_status == 'y' || global_status == 'Y'){
        for (auto contact_to_update = contactBook.begin(); contact_to_update != contactBook.end(); contact_to_update++){
            for (Contact found_contact : list_to_update){
                if (*contact_to_update == found_contact){
                    (*contact_to_update).show();
                    cout<<"\nWant to update contact? (y/n)"<<endl;
                    cin>>status;
                    cin.ignore();
                    if (status == 'y' || status == 'Y'){
                        Contact temporary_contact = createContactByInput();
                        *contact_to_update = temporary_contact;
                    }
                }
            }
        }
    } 
}

bool ContactBook::compareByFirstName(const Contact& contact1, const Contact& contact2){
    return contact1.get_firstName() < contact2.get_firstName();
}

bool ContactBook::compareBySecondName(const Contact& contact1, const Contact& contact2){
    return contact1.get_secondName() < contact2.get_secondName();
}

bool ContactBook::compareByLastName(const Contact& contact1, const Contact& contact2){
    string lastName1 = (contact1.get_lastName().empty() ? "zzzzzzzzzz" : contact1.get_lastName());
    string lastName2 = (contact2.get_lastName().empty() ? "zzzzzzzzzz" : contact2.get_lastName());
    return lastName1 < lastName2;
}

bool ContactBook::compareByBirthDate(const Contact& contact1, const Contact& contact2){
    string date1 = (contact1.get_birthDate().empty() ? "31-12-9999" : contact1.get_birthDate());
    string date2 = (contact2.get_birthDate().empty() ? "31-12-9999" : contact2.get_birthDate());
    return date1 < date2;
}

bool ContactBook::compareByAddress(const Contact& contact1, const Contact& contact2){
    string address1 = (contact1.get_address().empty() ? "zzzzzzzzzz" : contact1.get_address());
    string address2 = (contact2.get_address().empty() ? "zzzzzzzzzz" : contact2.get_address());
    return address1 < address2;
}

bool ContactBook::compareByEmail(const Contact& contact1, const Contact& contact2){
    return contact1.get_email() < contact2.get_email();
}

bool ContactBook::compareByFirstNameDecr(const Contact& contact1, const Contact& contact2){
    return contact1.get_firstName() > contact2.get_firstName();
}

bool ContactBook::compareBySecondNameDecr(const Contact& contact1, const Contact& contact2){
    return contact1.get_secondName() > contact2.get_secondName();
}

bool ContactBook::compareByLastNameDecr(const Contact& contact1, const Contact& contact2){
    string lastName1 = (contact1.get_lastName().empty() ? "zzzzzzzzzz" : contact1.get_lastName());
    string lastName2 = (contact2.get_lastName().empty() ? "zzzzzzzzzz" : contact2.get_lastName());
    return lastName1 > lastName2;
}

bool ContactBook::compareByBirthDateDecr(const Contact& contact1, const Contact& contact2){
    string date1 = (contact1.get_birthDate().empty() ? "31-12-9999" : contact1.get_birthDate());
    string date2 = (contact2.get_birthDate().empty() ? "31-12-9999" : contact2.get_birthDate());
    return date1 > date2;
}

bool ContactBook::compareByAddressDecr(const Contact& contact1, const Contact& contact2){
    string address1 = (contact1.get_address().empty() ? "zzzzzzzzzz" : contact1.get_address());
    string address2 = (contact2.get_address().empty() ? "zzzzzzzzzz" : contact2.get_address());
    return address1 > address2;
}

bool ContactBook::compareByEmailDecr(const Contact& contact1, const Contact& contact2){
    return contact1.get_email() > contact2.get_email();
}

void ContactBook::showSortMenu(){
    cout<<"\n------SORT MENU------\n"<<endl;
    cout << "1. Sort by First Name (A-Z)" << endl;
    cout << "2. Sort by First Name (Z-A)" << endl;
    cout << "3. Sort by Second Name (A-Z)" << endl;
    cout << "4. Sort by Second Name (Z-A)" << endl;
    cout << "5. Sort by Last Name (A-Z)" << endl;
    cout << "6. Sort by Last Name (Z-A)" << endl;
    cout << "7. Sort by Birth Date (oldest first)" << endl;
    cout << "8. Sort by Birth Date (newest first)" << endl;
    cout << "9. Sort by Address (A-Z)" << endl;
    cout << "10. Sort by Address (Z-A)" << endl;
    cout << "11. Sort by Email (A-Z)" << endl;
    cout << "12. Sort by Email (Z-A)" << endl;
    cout << "13. Cancel" << endl;
    cout << "Choose sorting option: ";
}

void ContactBook::sortContacts(){
    int criteria;
    
    showSortMenu();

    cin>>criteria;
    cin.ignore();

    switch (criteria)
    {
    case 1:
        contactBook.sort(compareByFirstName);
        break;
    case 2:
        contactBook.sort(compareByFirstNameDecr);
        break;
    case 3:
        contactBook.sort(compareBySecondName);
        break;
    case 4:
        contactBook.sort(compareBySecondName);
        break;
    case 5:
        contactBook.sort(compareByLastName);
        break;
    case 6:
        contactBook.sort(compareByLastNameDecr);
        break;
    case 7:
        contactBook.sort(compareByBirthDate);
        break;
    case 8:
        contactBook.sort(compareByBirthDateDecr);
        break;
    case 9:
        contactBook.sort(compareByAddress);
        break;
    case 10:
        contactBook.sort(compareByAddressDecr);
        break;
    case 11:
        contactBook.sort(compareByEmail);
        break;
    case 12:
        contactBook.sort(compareByEmailDecr);
        break;
    case 13:
        break;
    default:
        cout<<"\nWrong sorting criteria!!\n"<<endl;
        return;
    }
}

void ContactBook::saveContacts(){
    if (!fileStorage.saveToFile(contactBook)){cout<<"\nError: can't open file!\n"<<endl;}
}

void ContactBook::loadContacts(ContactBook& contact_book){
    contactBook = fileStorage.loadFromFile(contactBook);
}