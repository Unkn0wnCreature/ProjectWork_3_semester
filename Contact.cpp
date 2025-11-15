#include "Contact.h"
#include <regex>
#include <stdexcept>
#include <ctime>
using namespace std;

Contact::Contact(string firstName, string secondName, string email, list<string> list_of_phone_numbers, string lastName, string birthDate, string address){
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
    address = c.address;
    email = c.email;
    list_of_phone_numbers = c.list_of_phone_numbers;
}

Contact::~Contact(){}

bool Contact::set_firstName(string& firstName){
    string trimmed = trim(firstName);
    if (!isValidName(trimmed)){return false;}
    this->firstName = trimmed;
    return true;

}

bool Contact::set_secondName(string& secondName){
    string trimmed = trim(secondName);
    if (!isValidName(trimmed)){return false;}
    this->secondName = trimmed;
    return true;
}

bool Contact::set_lastName(string& lastName){
    string trimmed = trim(lastName);
    if (!isValidName(trimmed)){return false;}
    this->lastName = trimmed;
    return true;
}

bool Contact::set_birthDate(string& birthDate){
    string trimmed = trim(birthDate);
    if (!isValidDate(trimmed)){return false;}
    this->birthDate = trimmed;
    return true;
}

bool Contact::set_address(string& address){
    this->address = trim(address);
    return true;
}

bool Contact::set_email(string& email){
    string trimmed = trim(email);
    if (!isValidEmail(trimmed)){return false;}
    this->email = trimmed;
    return true;
}

bool Contact::set_list_of_phones(list<string> list_of_phones){
    list<string> temp_list_of_phones;
    for (string str : list_of_phones){
        string trimmed = trim(str);
        if (!isValidPhone(trimmed)){return false;}
        
        temp_list_of_phones.emplace_back(trimmed);
    }

    this->list_of_phone_numbers = temp_list_of_phones;

    return true;
}

string Contact::get_firstName() const {return firstName;}
string Contact::get_secondName() const {return secondName;}
string Contact::get_lastName() const {return lastName;}
string Contact::get_birthDate() const {return birthDate;}
string Contact::get_address() const {return address;}
string Contact::get_email() const {return email;}
list<string> Contact::get_list_of_phones() const {return list_of_phone_numbers;}

bool Contact::isValidName(const string& name) const {
    if (name.empty()) return true;
    
    regex pattern("^[a-zA-Zа-яА-Я][a-zA-Zа-яА-Я0-9\\-\\s]*[a-zA-Zа-яА-Я0-9]$");
        return regex_match(trim(name), pattern);
}

bool Contact::isValidEmail(const string& email) const {
    regex pattern("^[a-zA-Z0-9]+@[a-zA-Z0-9]+\\.[a-zA-Z0-9]+$");
    return regex_match(trim(email), pattern);
}

bool Contact::isValidPhone(const string& phoneNumber) const {
    
    string cleanPhone = phoneNumber;
    cleanPhone.erase(remove_if(cleanPhone.begin(), cleanPhone.end(),
                     [](char c) { return !isdigit(c) && c != '+'; }), cleanPhone.end());
    
    
    regex pattern("^(\\+7|8)[\\s(-]*(\\d{3})[\\s)-]*(\\d{3})[\\s-]*(\\d{2})[\\s-]*(\\d{2})$");
    return regex_match(trim(cleanPhone), pattern);
}

bool Contact::isValidDate(const string& date) const {
    
    if (date.empty() || date == "") return true;
    if (date.length() != 10) return false;
    if (date[2] != '-' || date[5] != '-') return false;
    int year, month, day;
    try {
        day = stoi(date.substr(0, 2));
        month = stoi(date.substr(3, 2));
        year = stoi(date.substr(6, 4));
    } catch (...) {
        return false;
    }
    
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[1] = 29;
    }
    if (day > daysInMonth[month - 1]) return false;
    
    time_t t = std::time(nullptr);
    tm* now = std::localtime(&t);
    int currentYear = now->tm_year + 1900;
    int currentMonth = now->tm_mon + 1;
    int currentDay = now->tm_mday;
    if (year > currentYear) return false;
    if (year == currentYear && month > currentMonth) return false;
    if (year == currentYear && month == currentMonth && day > currentDay) return false;
    return true;
}

bool Contact::isValidAddress(const string& address) const{
    if (address.empty()){return true;}

    regex pattern("^[a-zA-Zа-яА-Я0-9\\s\\-,.#№()/]+$");
    return regex_match(trim(address), pattern);
}

string Contact::normalizePhoneNumber(const string& phoneNumber){
    string result;
    for (char c : phoneNumber) {
        if (std::isdigit(c) || c == '+') {
            result += c;
        }
    }
    
    if (result.length() == 11 && result[0] == '8') {
        result[0] = '7';
        result = "+" + result;
    } else if (result.length() == 10) {
        result = "+7" + result;
    }
    
    return result;
}

string Contact::trim(const string& string) const{
    size_t start = string.find_first_not_of(" \t\n\r");
    size_t end = string.find_last_not_of(" \t\n\r");
    if (start == string::npos){return "";}
    return string.substr(start, end - start + 1);
}

bool Contact::addPhoneNumber(const string& phoneNumber){
    if (!isValidPhone(phoneNumber)){return false;}
    this->list_of_phone_numbers.push_back(phoneNumber);
    return true;
}

void Contact::show(){
    cout<<"First name: " << firstName <<endl;
    cout<<"Second name: " << secondName <<endl;
    cout<<"Last name: " << ((lastName.empty()) ? "Not stated":lastName) <<endl;
    cout<<"Birth date: " << ((birthDate.empty()) ? "Not stated":birthDate) <<endl;
    cout<<"Address: " << ((address.empty()) ? "Not stated":address) <<endl;
    cout<<"Email: " << email <<endl;
    cout<<"Phone numbers: "<<endl;
    for (string phone_number : list_of_phone_numbers){
        cout<<"\t"<< phone_number <<endl;
    }
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

bool Contact::findByFirstName(const string& string_to_find){
    if (string_to_find.empty()) return true;
    return this->firstName.find(string_to_find) != string::npos;
}

bool Contact::findBySecondName(const string& string_to_find){
    if (string_to_find.empty()) return true;
    return this->secondName.find(string_to_find) != string::npos;
}

bool Contact::findByLastName(const string& string_to_find){
    if (string_to_find.empty()) return true;
    if (this->lastName.empty()) return false;
    return this->lastName.find(string_to_find) != string::npos;
}

bool Contact::findByBirthDate(const string& string_to_find){
    if (string_to_find.empty()) return true;
    if (this->birthDate.empty()) return false;
    return this->birthDate.find(string_to_find) != string::npos;
}

bool Contact::findByAddress(const string& string_to_find){
    if (string_to_find.empty()) return true;
    if (this->address.empty()) return false;
    return this->address.find(string_to_find) != string::npos;
}

bool Contact::findByEmail(const string& string_to_find){
    if (string_to_find.empty()) return true;
    return this->email.find(string_to_find) != string::npos;
}

bool Contact::findByPhoneNumber(const string& string_to_find){
    if (string_to_find.empty()) return true;
    for (const string& phone_number : this->list_of_phone_numbers){
        if (phone_number.find(string_to_find) != string::npos){
            return true;
        }
    }
    return false;
}

bool Contact::findByString(const string& string_to_find){
    return ((findByFirstName(string_to_find) || findBySecondName(string_to_find) ||
        findByLastName(string_to_find) || findByBirthDate(string_to_find) || findByAddress(string_to_find) ||
            findByEmail(string_to_find) || findByPhoneNumber(string_to_find)));
}