#include <iostream>
#include "ContactBook.h"
#include "Contact.h"
#include "ConsoleUI.h"
#include "FileStorage.h"
#include "ContactBook.cpp"
#include "Contact.cpp"
#include "ConsoleUI.cpp"
#include "FileStorage.cpp"
using namespace std;

int main(){
    ContactBook contact_book;
    ConsoleUI consoleUI;

    consoleUI.run(contact_book);
    
    return 0;
}
