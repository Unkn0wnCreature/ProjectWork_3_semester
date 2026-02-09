#include "DBStorage.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QtSql/QSqlDriver>

DatabaseStorage::DatabaseStorage(QObject *parent) : QObject(parent){
    /*
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL", "contactbook_db"));
    db->setHostName("localhost");
    db->setPort(5432);
    db->setDatabaseName("contact_book");
    db->setUserName("postgres");
    db->setPassword("1234");
    */
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE", "contactbook_db"));
    db->setDatabaseName("contacts.db");

    qDebug() << "Using SQLite database: contacts.db";
}

DatabaseStorage::~DatabaseStorage(){
    disconnect();
    if (db){
        delete db;
        db = nullptr;
    }
}

bool DatabaseStorage::connectToDatabase(){
    if (!db->open()) {
        qDebug() << "Database connection error:" << db->lastError().text();
        return false;
    }

    createTables();
    return true;
}

bool DatabaseStorage::isConnected() const{
    return (db && db->isOpen());
}

bool DatabaseStorage::disconnect(){
    if (isConnected()){
        db->close();
        return true;
    }
    return false;
}

/*
bool DatabaseStorage::createTables(){
    QSqlQuery query(*db);

    bool result = query.exec(
        "CREATE TABLE IF NOT EXISTS contacts ("
        "id SERIAL PRIMARY KEY,"
        "firstName TEXT NOT NULL,"
        "secondName TEXT NOT NULL,"
        "lastName TEXT,"
        "address TEXT,"
        "birthDate TEXT,"
        "email TEXT UNIQUE NOT NULL,"
        "phones TEXT NOT NULL)"
        );

    if (!result) {
        qDebug() << "Create table error:" << query.lastError().text();
    }
    return result;
}
*/

bool DatabaseStorage::createTables(){
    QSqlQuery query(*db);

    bool result = query.exec(
        "CREATE TABLE IF NOT EXISTS contacts ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "firstName TEXT NOT NULL,"
        "secondName TEXT NOT NULL,"
        "lastName TEXT,"
        "address TEXT,"
        "birthDate TEXT,"
        "email TEXT UNIQUE NOT NULL,"
        "phones TEXT NOT NULL)"
        );

    if (!result) {
        qDebug() << "Create table error:" << query.lastError().text();
    }
    return result;
}

bool DatabaseStorage::saveToDatabase(const QList<Contact> &contactBook){
    if (!isConnected()) {
        qDebug() << "Not connected to database";
        return false;
    }

    QSqlQuery clearQuery(*db);
    if (!clearQuery.exec("DELETE FROM contacts")) {
        qDebug() << "Clear table error:" << clearQuery.lastError().text();
        return false;
    }

    QString sql = "INSERT INTO contacts (firstName, secondName, lastName, "
                  "address, birthDate, email, phones) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?)";
    QSqlQuery query(*db);
    query.prepare(sql);

    for (const Contact& contact : contactBook){
        query.addBindValue(contact.get_firstName());
        query.addBindValue(contact.get_secondName());
        query.addBindValue(contact.get_lastName());
        query.addBindValue(contact.get_address());
        query.addBindValue(contact.get_birthDate());
        query.addBindValue(contact.get_email());
        query.addBindValue(contact.get_list_of_phones().join("|"));

        if (!query.exec()){
            qDebug() << "Insert error for contact" << contact.get_email()
            << ":" << query.lastError().text();
            return false;
        }
    }
    return true;
}

QList<Contact> DatabaseStorage::loadFromDatabase(){
    QList<Contact> contacts;

    if (!isConnected()) {
        qDebug() << "Not connected to database";
        return contacts;
    }

    QSqlQuery query("SELECT firstName, secondName, lastName, "
                    "address, birthDate, email, phones "
                    "FROM contacts", *db);

    if (!query.exec()) {
        qDebug() << "Select error:" << query.lastError().text();
        return contacts;
    }

    while (query.next()){
        contacts.append(contactFromQuery(query));
    }

    qDebug() << "Loaded" << contacts.size() << "contacts from database";
    return contacts;
}

Contact DatabaseStorage::contactFromQuery(const QSqlQuery &query){
    Contact contact;

    contact.set_firstName(query.value("firstName").toString());
    contact.set_secondName(query.value("secondName").toString());
    contact.set_lastName(query.value("lastName").toString());
    contact.set_address(query.value("address").toString());
    contact.set_birthDate(query.value("birthDate").toString());
    contact.set_email(query.value("email").toString());

    QString phonesStr = query.value("phones").toString();
    if (!phonesStr.isEmpty()) {
        contact.set_list_of_phones(phonesStr.split("|", Qt::SkipEmptyParts));
    }

    return contact;
}

QString DatabaseStorage::getLastError() const {
    if (db) {
        return db->lastError().text();
    }
    return "Database not initialized";
}
