#pragma once

#include "Contact.h"
#include <QList>
#include <QString>
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QVariant>
#include <QDebug>

class DatabaseStorage : public QObject{
    Q_OBJECT
private:
    QSqlDatabase* db = nullptr;

public:
    explicit DatabaseStorage(QObject *parent = nullptr);
    ~DatabaseStorage();

    bool connectToDatabase();
    bool disconnect();
    bool isConnected() const;

    bool saveToDatabase(const QList<Contact>& contactBook);
    QList<Contact> loadFromDatabase();
    Contact contactFromQuery(const QSqlQuery& query);

    bool createTables();
    bool clearDatabase();

    QString getLastError() const;
};
