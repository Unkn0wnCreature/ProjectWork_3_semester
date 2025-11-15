#include "ConsoleUI.h"
#include <iostream>

ConsoleUI::ConsoleUI(){}
ConsoleUI::~ConsoleUI(){}

void ConsoleUI::show(){
    cout<<"\n------M E N U------\n"<<endl;
    cout<<"1. Show contact book."<<endl;
    cout<<"2. Add contact."<<endl;
    cout<<"3. Delete contacts."<<endl;
    cout<<"4. Update contacts."<<endl;
    cout<<"5. Sort contacts by criteria."<<endl;
    cout<<"6. Finish programm"<<endl;

    cout<<"\nChoose option: ";
}

void ConsoleUI::run(ContactBook& contactBook){
    int option;

    show();
    cin>>option;
    cin.ignore();

    while (option > 0 && option < 7){
        switch (option){
            case 1:
                contactBook.loadContacts(contactBook);
                contactBook.showContacts();
                break;
            case 2:
                contactBook.loadContacts(contactBook);
                contactBook.addContact(contactBook.createContactByInput());
                contactBook.saveContacts();
                break;
            case 3:
                contactBook.loadContacts(contactBook);
                contactBook.deleteContact();
                contactBook.saveContacts();
                break;
            case 4:
                contactBook.loadContacts(contactBook);
                contactBook.updateContact();
                contactBook.saveContacts();
                break;
            case 5:
                contactBook.loadContacts(contactBook);
                contactBook.sortContacts();
                contactBook.saveContacts();
                break;
            case 6:
                cout<<"Programm finished!"<<endl;
                return;
        }

        show();
        cin>>option;
        cin.ignore();
    }
}