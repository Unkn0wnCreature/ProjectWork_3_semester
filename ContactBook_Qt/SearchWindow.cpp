#include "SearchWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>

SearchWindow::SearchWindow(QDialog *parent) : QDialog(parent){
    setWindowTitle("Поиск");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QFormLayout* formLayout = new QFormLayout();

    firstNameEdit = new QLineEdit(this);
    secondNameEdit = new QLineEdit(this);
    lastNameEdit = new QLineEdit(this);
    addressEdit = new QLineEdit(this);
    birthEdit = new QLineEdit(this);
    emailEdit = new QLineEdit(this);
    phoneEdit = new QLineEdit(this);

    formLayout->addRow("Имя:", firstNameEdit);
    formLayout->addRow("Фамилия:", secondNameEdit);
    formLayout->addRow("Отчество:", lastNameEdit);
    formLayout->addRow("Адрес:", addressEdit);
    formLayout->addRow("Дата рождения:", birthEdit);
    formLayout->addRow("Почта:", emailEdit);
    formLayout->addRow("Телефон:", phoneEdit);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    QPushButton *acceptButton = new QPushButton("Ок");
    QPushButton *cancelButton = new QPushButton("Отмена");

    buttonsLayout->addWidget(acceptButton);
    buttonsLayout->addWidget(cancelButton);

    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);

    connect(acceptButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

SearchWindow::~SearchWindow(){}

void SearchWindow::clear(){
    firstNameEdit->clear();
    secondNameEdit->clear();
    lastNameEdit->clear();
    birthEdit->clear();
    addressEdit->clear();
    emailEdit->clear();
    phoneEdit->clear();
}

QList<QString> SearchWindow::getCriteria(){
    return {firstNameEdit->text(),
    secondNameEdit->text(),
    lastNameEdit->text(),
    birthEdit->text(),
    addressEdit->text(),
    emailEdit->text(),
    phoneEdit->text()};
}
