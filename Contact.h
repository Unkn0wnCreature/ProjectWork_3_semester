#pragma once
#include <QString>
#include <iostream>
#include <QList>
#include <QMessageBox>
using namespace std;

class Contact {
    private:
    QString firstName;
    QString secondName;
    QString lastName;
    QString birthDate;
    QString address;
    QString email;
    QList<QString> list_of_phone_numbers;

    public:
    Contact(QString firstName = "", QString secondName = "", QString email = "", QList<QString> list_of_phone_numbers = {}, QString lastName = "", QString birthDate = "", QString address = "");
    Contact(const Contact &c);
    ~Contact();

    bool set_firstName(QString firstName);
    bool set_secondName(QString secondName);
    bool set_lastName(QString lastName);
    bool set_birthDate(QString birthDate);
    bool set_address(QString address);
    bool set_email(QString email);
    bool set_list_of_phones(QList<QString> list_of_phones);

    QString get_firstName() const;
    QString get_secondName() const;
    QString get_lastName() const;
    QString get_birthDate() const;
    QString get_address() const;
    QString get_email() const;
    QList<QString> get_list_of_phones() const;

    bool isValidName(const QString& name) const;
    bool isValidEmail(const QString& email) const;
    bool isValidPhone(const QString& phone) const;
    bool isValidDate(const QString& date) const;
    bool isValidAddress(const QString& address) const;
    bool isValidContact() const;

    QString normalizePhone(const QString& phone) const;
    QString trim(const QString& string) const;
    bool addPhoneNumber(const QString& PhoneNumber);

    void show();

    Contact& operator=(const Contact& other);
    bool operator==(const Contact& other) const;

    bool findByFirstName(const QString& string_to_find);
    bool findBySecondName(const QString& string_to_find);
    bool findByLastName(const QString& string_to_find);
    bool findByBirthDate(const QString& string_to_find);
    bool findByAddress(const QString& string_to_find);
    bool findByEmail(const QString& string_to_find);
    bool findByPhoneNumber(const QString& string_to_find);
    bool findByString(const QString& string_to_find);
};

