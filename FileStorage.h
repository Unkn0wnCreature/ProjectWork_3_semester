#pragma once
#include "Contact.h"
#include <QString>
#include <QList>
using namespace std;

class FileStorage {
private:
    QString filename;

public:
    FileStorage(QString filename = "contacts.txt");
    ~FileStorage();

    bool saveToFile(const QList<Contact>& contactBook);
    QList<Contact> loadFromFile();

    QString getFileName() const;
    void setFileName(const QString& newFileName){filename = newFileName;}
};
