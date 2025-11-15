#pragma once
#include "Contact.h"
#include <vector>
#include <string>
using namespace std;

class FileStorage {
private:
    string filename;

public:
    FileStorage(string filename = "contacts.txt");
    ~FileStorage();

    bool saveToFile(const list<Contact>& contactBook);
    list<Contact> loadFromFile(const list<Contact>& contactBook);

    string getFileName() const;
};