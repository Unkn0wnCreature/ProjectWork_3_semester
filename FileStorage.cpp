#include "FileStorage.h"
#include "ContactBook.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

FileStorage::FileStorage(string filename){
    this->filename = filename;
}

FileStorage::~FileStorage(){}

bool FileStorage::saveToFile(const list<Contact>& contactBook){
    ofstream file(filename);

    if (!file.is_open()){return false;}
    else{
        file<< contactBook.size() <<endl;

        for (const Contact& contact : contactBook){
            file<< contact.get_firstName() <<endl;
            file<< contact.get_secondName() <<endl;
            file<< contact.get_lastName() <<endl;
            file<< contact.get_birthDate() <<endl;
            file<< contact.get_address() <<endl;
            file<< contact.get_email() <<endl;

            list<string> phones = contact.get_list_of_phones();
            file<< phones.size() <<endl;

            for (const string& phone : phones){
                file<< phone <<endl;
            }
            file<<"------"<<endl;
        }
        file.close();
        cout<<"\nSuccessfully saved "<< contactBook.size() <<" contacts to "<< filename <<endl;
        return true;
    }
}

list<Contact> FileStorage::loadFromFile(const list<Contact>& contactBook){
    list<Contact> contacts;
    ifstream file(filename);

    if (!file.is_open()){return contacts;}
    else{
        size_t contactCount;
        file>>contactCount;
        file.ignore();

        for (size_t i = 0; i < contactCount; ++i){
            string firstName, secondName, lastName, birthDate, address, email;

            getline(file, firstName);
            getline(file, secondName);
            getline(file, lastName);
            getline(file, birthDate);
            getline(file, address);
            getline(file, email);

            size_t phoneCount;
            file>>phoneCount;
            file.ignore();

            list<string> phones;
            for (size_t j = 0; j < phoneCount; ++j){
                string phone;
                getline(file, phone);
                phones.push_back(phone);
            }
            string separator;
            getline(file, separator);

            Contact contact(firstName, secondName, email, phones, lastName, birthDate, address);
            contacts.push_back(contact);
        }
        file.close();
        cout<<"\nSuccesfully loaded "<< contacts.size() <<" contacts from "<< filename <<endl;

    }
    return contacts;
}