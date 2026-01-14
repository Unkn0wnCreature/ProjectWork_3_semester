#include "Contact.h"
#include <regex>
#include <iostream>
#include <ctime>
#include <QRegularExpression>
#include <QChar>

using namespace std;

Contact::Contact(QString firstName, QString secondName, QString email, QList<QString> list_of_phone_numbers, QString lastName, QString birthDate, QString address){
    this->firstName = firstName;
    this->secondName = secondName;
    this->lastName = lastName;
    this->birthDate = birthDate;
    this->address = address;
    this->email = email;
    this->list_of_phone_numbers = list_of_phone_numbers;
}

Contact::Contact(const Contact& c){
    firstName = c.firstName;
    secondName = c.secondName;
    lastName = c.lastName;
    birthDate = c.birthDate;
    address = c.address;
    email = c.email;
    list_of_phone_numbers = c.list_of_phone_numbers;
}

Contact::~Contact(){}

bool Contact::set_firstName(QString firstName){
    QString trimmed = trim(firstName);
    //if (!isValidName(trimmed)){return false;}
    this->firstName = trimmed;
    return true;

}

bool Contact::set_secondName(QString secondName){
    QString trimmed = trim(secondName);
    //if (!isValidName(trimmed)){return false;}
    this->secondName = trimmed;
    return true;
}

bool Contact::set_lastName(QString lastName){
    QString trimmed = trim(lastName);
    //if (!isValidName(trimmed)){return false;}
    this->lastName = trimmed;
    return true;
}

bool Contact::set_birthDate(QString birthDate){
    QString trimmed = trim(birthDate);
    //if (!isValidDate(trimmed)){return false;}
    this->birthDate = trimmed;
    return true;
}

bool Contact::set_address(QString address){
    this->address = trim(address);
    return true;
}

bool Contact::set_email(QString email){
    QString trimmed = trim(email);
    //if (!isValidEmail(trimmed)){return false;}
    this->email = trimmed;
    return true;
}

bool Contact::set_list_of_phones(QList<QString> list_of_phones){
    QList<QString> temp_list_of_phones;
    for (QString str : list_of_phones){
        QString trimmed = trim(str);
        
        temp_list_of_phones.append(normalizePhone(trimmed));
    }

    this->list_of_phone_numbers = temp_list_of_phones;

    return true;
}

QString Contact::get_firstName() const {return firstName;}
QString Contact::get_secondName() const {return secondName;}
QString Contact::get_lastName() const {return lastName;}
QString Contact::get_birthDate() const {return birthDate;}
QString Contact::get_address() const {return address;}
QString Contact::get_email() const {return email;}
QList<QString> Contact::get_list_of_phones() const {return list_of_phone_numbers;}

bool Contact::isValidName(const QString& name) const {
    if (name.isEmpty()){return true;}
    
    QRegularExpression pattern("^[a-zA-Zа-яА-Я][a-zA-Zа-яА-Я0-9\\-\\s]*[a-zA-Zа-яА-Я0-9]$");
        return pattern.match(trim(name)).hasMatch();
}

bool Contact::isValidEmail(const QString& email) const {
    QRegularExpression pattern("^[a-zA-Z0-9]+@[a-zA-Z0-9]+\\.[a-zA-Z0-9]+$");
    return pattern.match(trim(email)).hasMatch();
}

bool Contact::isValidPhone(const QString& phoneNumber) const {
    
    QString cleanPhone;
    for (const QChar& c : phoneNumber)
    {
        if (c.isDigit() || c == '+'){cleanPhone.append(c);}
    }
    
    QRegularExpression pattern("^(\\+7|8|7)[\\s(-]*(\\d{3})[\\s)-]*(\\d{3})[\\s-]*(\\d{2})[\\s-]*(\\d{2})$");
    return pattern.match(trim(cleanPhone)).hasMatch();
}

bool Contact::isValidDate(const QString& date) const {
    
    if (date.isEmpty() || date == "") return true;
    if (date.length() != 10) return false;
    if (date[2] != '-' || date[5] != '-') return false;
    bool ok1, ok2, ok3;

    int day = date.mid(0, 2).toInt(&ok1);
    int month = date.mid(3, 2).toInt(&ok2);
    int year = date.mid(6, 4).toInt(&ok3);

    if (!ok1 || !ok2 || !ok3){return false;}
    
    if (day < 1){return false;}
    
    QList<int> daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[1] = 29;
    }

    if (month <= 0 || month > daysInMonth.size()){return false;}
    if (day > daysInMonth[month - 1]){return false;}
    
    time_t t = std::time(nullptr);
    tm* now = std::localtime(&t);
    int currentYear = now->tm_year + 1900;
    int currentMonth = now->tm_mon + 1;
    int currentDay = now->tm_mday;
    if (year > currentYear) return false;
    if (year == currentYear && month > currentMonth){return false;}
    if (year == currentYear && month == currentMonth && day > currentDay) return false;
    return true;
}

bool Contact::isValidAddress(const QString& address) const{
    if (address.isEmpty()){return true;}

    QRegularExpression pattern("^[a-zA-Zа-яА-Я0-9\\s\\-,.#№()/]+$");
    return pattern.match(trim(address)).hasMatch();
}

bool Contact::isValidContact() const{
    bool validationStatus = true;
    if (!isValidName(firstName) || firstName.isEmpty()){
        validationStatus = false;
    }
    if (!isValidName(secondName) || secondName.isEmpty()){
        validationStatus = false;
    }
    if (!isValidName(lastName)){
        validationStatus = false;
    }
    if (!isValidEmail(email) || email.isEmpty()){
        validationStatus = false;
    }
    if (!isValidAddress(address)){
        validationStatus = false;
    }
    if (!isValidDate(birthDate)){
        validationStatus = false;
    }
    if (list_of_phone_numbers.size() <= 0){
        validationStatus = false;
    }

    return validationStatus;
}

QString Contact::normalizePhone(const QString& phone) const {
    QString normalized;

    for (QChar c : phone){
        if (c.isDigit() || c == '+'){normalized.append(c);}
    }

    if (normalized.length() == 11 && normalized[0] == '8'){
        normalized[0] = '7';
        normalized = '+' + normalized;
    } else if (normalized.length() == 10){
        normalized = "+7" + normalized;
    } else if (normalized.length() == 11 && normalized[0] == '7'){
        normalized = '+' + normalized;
    }

    return normalized;
}

QString Contact::trim(const QString& string) const{
    return string.trimmed();
}

bool Contact::addPhoneNumber(const QString& phoneNumber){
    QString trimmed = trim(phoneNumber);
    if (!isValidPhone(trimmed)){return false;}
    this->list_of_phone_numbers.append(normalizePhone(trimmed));
    return true;
}

Contact& Contact::operator=(const Contact& other){
    this->firstName = other.firstName;
    this->secondName = other.secondName;
    this->lastName = other.lastName;
    this->birthDate = other.birthDate;
    this->address = other.address;
    this->email = other.email;
    this->list_of_phone_numbers = other.list_of_phone_numbers;

    return *this;
}

bool Contact::operator==(const Contact& other) const {
    return (firstName == other.firstName &&
            secondName == other.secondName &&
            lastName == other.lastName &&
            birthDate == other.birthDate &&
            address == other.address &&
            email == other.email &&
            list_of_phone_numbers == other.list_of_phone_numbers);
}

bool Contact::findByFirstName(const QString& string_to_find){
    if (string_to_find.isEmpty()){return true;}
    return firstName.contains(string_to_find, Qt::CaseInsensitive);
}

bool Contact::findBySecondName(const QString& string_to_find){
    if (string_to_find.isEmpty()){return true;}
    return secondName.contains(string_to_find, Qt::CaseInsensitive);
}

bool Contact::findByLastName(const QString& string_to_find){
    if (string_to_find.isEmpty()){return true;}
    if (this->lastName.isEmpty()){return false;}
    return lastName.contains(string_to_find, Qt::CaseInsensitive);
}

bool Contact::findByBirthDate(const QString& string_to_find){
    if (string_to_find.isEmpty()){return true;}
    if (birthDate.isEmpty()){return false;}
    return birthDate.contains(string_to_find, Qt::CaseInsensitive);
}

bool Contact::findByAddress(const QString& string_to_find){
    if (string_to_find.isEmpty()){return true;}
    if (address.isEmpty()){return false;}
    return address.contains(string_to_find, Qt::CaseInsensitive);
}

bool Contact::findByEmail(const QString& string_to_find){
    if (string_to_find.isEmpty()){return true;}
    return email.contains(string_to_find, Qt::CaseInsensitive);
}

bool Contact::findByPhoneNumber(const QString& string_to_find){
    if (string_to_find.isEmpty()){return true;}
    for (const QString& phone_number : list_of_phone_numbers){
        if (phone_number.contains(string_to_find, Qt::CaseInsensitive)){
            return true;
        }
    }
    return false;
}

bool Contact::findByString(const QString& string_to_find){
    return ((findByFirstName(string_to_find) ||
             findBySecondName(string_to_find) ||
             findByLastName(string_to_find) ||
             findByBirthDate(string_to_find) ||
             findByAddress(string_to_find) ||
             findByEmail(string_to_find) ||
             findByPhoneNumber(string_to_find)));
}
