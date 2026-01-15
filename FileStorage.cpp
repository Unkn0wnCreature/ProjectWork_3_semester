#include "FileStorage.h"
#include "ContactBook.h"
#include "Contact.h"
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
using namespace std;

FileStorage::FileStorage(QString filename) : filename(filename){
    if (filename.isEmpty()){
        this->filename = QCoreApplication::applicationDirPath() + "/contacts.txt";
    }
}

FileStorage::~FileStorage(){}

bool FileStorage::saveToFile(const QList<Contact>& contactBook){
    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return false;
    }

    QTextStream out(&file);

    out << contactBook.size() << "\n";

    for (const Contact& contact : contactBook){
        out << contact.get_firstName() << "\n";
        out << contact.get_secondName() << "\n";
        out << contact.get_lastName() << "\n";
        out << contact.get_birthDate() << "\n";
        out << contact.get_address() << "\n";
        out << contact.get_email() << "\n";

        QList<QString> phones = contact.get_list_of_phones();
        out << phones.size() << "\n";

        for (const QString& phone : phones){
            out << phone << "\n";
        }
        out <<"------"<< "\n";
    }
    file.close();
    //cout<<"\nSuccessfully saved "<< contactBook.size() <<" contacts to "<< filename <<endl;
    return true;
}


QList<Contact> FileStorage::loadFromFile(){
    QList<Contact> contacts;
    QFile file(filename);

    if (!file.exists()){return contacts;}
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return contacts;
    }

    QTextStream in(&file);

    bool ok;
    QString line = in.readLine();
    int contactCount = line.toInt(&ok);

    if (!ok || contactCount < 0){
        file.close();
        //QMessageBox box("123");
        //qDebug()<<"error to open";
        return contacts;
    }

    for (int i = 0; i < contactCount; ++i){
        QString firstName = in.readLine();
        QString secondName = in.readLine();
        QString lastName = in.readLine();
        QString birthDate = in.readLine();
        QString address = in.readLine();
        QString email = in.readLine();

        QString phoneCountStr = in.readLine();
        int phoneCount = phoneCountStr.toInt(&ok);

        QList<QString> phones;
        for (int j = 0; j < phoneCount; ++j){
            QString phone = in.readLine();
            phones.append(phone);
        }
        in.readLine();

        Contact contact(firstName, secondName, email, phones, lastName, birthDate, address);
        contacts.append(contact);
    }
    file.close();
    return contacts;
}
