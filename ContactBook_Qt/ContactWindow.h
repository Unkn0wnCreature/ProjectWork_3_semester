#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QDialog>
#include "Contact.h"

class ContactWindow : public QDialog
{
public:
    ContactWindow(QDialog *parent = nullptr);
    ~ContactWindow();
    Contact updateContact();

    void addPhone();
    void deletePhone();
    void setContact(const Contact& contact);
    Contact getContact() const;

private:
    QLineEdit *firstNameEdit, *secondNameEdit, *lastNameEdit, *addressEdit, *birthEdit, *emailEdit, *phoneEdit;
    QListWidget *phoneList;
};
