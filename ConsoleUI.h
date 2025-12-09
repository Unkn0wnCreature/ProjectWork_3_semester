#pragma once
#include "ContactBook.h"
#include "FileStorage.h"
#include "FileStorage.h"

class ConsoleUI {
    public:
    ConsoleUI();
    ~ConsoleUI();

    void show();
    void run(ContactBook& contactBook);
};
