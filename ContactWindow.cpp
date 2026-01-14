#include "ContactWindow.h"

ContactWindow::ContactWindow(QDialog *parent) : QDialog(parent)
{
    setWindowTitle("Контакт");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QFormLayout* formLayout = new QFormLayout();

    firstNameEdit = new QLineEdit(this);
    secondNameEdit = new QLineEdit(this);
    lastNameEdit = new QLineEdit(this);
    addressEdit = new QLineEdit(this);
    birthEdit = new QLineEdit(this);
    emailEdit = new QLineEdit(this);
    phoneEdit = new QLineEdit(this);
    phoneList = new QListWidget(this);

    firstNameEdit->setPlaceholderText("Обязательное поле");
    secondNameEdit->setPlaceholderText("Обязательное поле");
    birthEdit->setPlaceholderText("ДД-ММ-ГГГГ");
    emailEdit->setPlaceholderText("Обязательное поле");

    formLayout->addRow("Имя:", firstNameEdit);
    formLayout->addRow("Фамилия:", secondNameEdit);
    formLayout->addRow("Отчество:", lastNameEdit);
    formLayout->addRow("Адрес:", addressEdit);
    formLayout->addRow("Дата рождения:", birthEdit);
    formLayout->addRow("Почта:", emailEdit);
    formLayout->addRow("Телефон:", phoneEdit);

    QHBoxLayout* phoneLayout = new QHBoxLayout();
    QPushButton *addPhoneButton = new QPushButton("Добавить");
    QPushButton *deletePhoneButton = new QPushButton("Удалить");

    phoneLayout->addWidget(addPhoneButton);
    phoneLayout->addWidget(deletePhoneButton);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    QPushButton *acceptButton = new QPushButton("Ok");
    QPushButton *cancelButton = new QPushButton("Cancel");

    buttonsLayout->addWidget(acceptButton);
    buttonsLayout->addWidget(cancelButton);

    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(phoneLayout);
    mainLayout->addWidget(phoneList);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);

    connect(addPhoneButton, &QPushButton::clicked, this, &ContactWindow::addPhone);
    connect(deletePhoneButton, &QPushButton::clicked, this, &ContactWindow::deletePhone);
    connect(acceptButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

ContactWindow::~ContactWindow(){}

void ContactWindow::addPhone()
{
    QString phone = phoneEdit->text().trimmed();

    if (!phone.isEmpty()){
        Contact tempContact;
        QString normalized = tempContact.normalizePhone(phone);
        if (tempContact.isValidPhone(phone)){

            bool phoneExists = false;
            for (int i = 0; i < phoneList->count(); ++i){
                if (phoneList->item(i)->text() == normalized){
                    phoneExists = true;
                    break;
                }
            }

            if (!phoneExists){
                phoneList->addItem(normalized);
                phoneEdit->clear();
            } else {
                QMessageBox::warning(this, "Предупреждение", "Данный номер уже существует!");
            }
        } else {
            QMessageBox::warning(this, "Некоректный номер", "Попробуйте ввести номер снова!");
        }
    }
}

void ContactWindow::deletePhone()
{
    int row = phoneList->currentRow();

    if (row >= 0){
        delete phoneList->takeItem(row);
    }
}

void ContactWindow::setContact(const Contact &contact)
{
    firstNameEdit->setText(contact.get_firstName());
    secondNameEdit->setText(contact.get_secondName());
    lastNameEdit->setText(contact.get_lastName());
    addressEdit->setText(contact.get_address());
    birthEdit->setText(contact.get_birthDate());
    emailEdit->setText(contact.get_email());

    phoneList->clear();
    for (const QString& phone : contact.get_list_of_phones()){
        phoneList->addItem(phone);
    }
}

Contact ContactWindow::getContact() const
{
    Contact contact;

    contact.set_firstName(firstNameEdit->text());
    contact.set_secondName(secondNameEdit->text());
    contact.set_lastName(lastNameEdit->text());
    contact.set_address(addressEdit->text());
    contact.set_birthDate(birthEdit->text());
    contact.set_email(emailEdit->text());

    QStringList phones;

    for (int i = 0; i < phoneList->count(); ++i){
        phones.append(phoneList->item(i)->text());
    }

    contact.set_list_of_phones(phones);

    return contact;
}
