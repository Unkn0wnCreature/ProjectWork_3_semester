#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>
#include "ContactBook.h"
#include "Contact.h"
#include "FileStorage.h"
#include <QDebug>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMenu();

    setNonEditableTable();

    loadContacts();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete contactBook;
    delete contact;
}

void MainWindow::setMenu(){
    QMenu* fileMenu = menuBar()->addMenu("Файл");
    fileMenu->addAction("Загрузить", this, &MainWindow::loadContacts);
    fileMenu->addAction("Сохранить", this, &MainWindow::saveContacts);
    fileMenu->addSeparator();
    fileMenu->addAction("Выход", qApp, &QApplication::quit);

    QMenu* editMenu = menuBar()->addMenu("Действия");
    editMenu->addAction("Добавить контакт", this, &MainWindow::addContact);
    editMenu->addAction("Обновить", this, &MainWindow::clearSearch);

    QMenu* searchMenu = menuBar()->addMenu("Поиск");
    searchMenu->addAction("Выполнить поиск", this, &MainWindow::searchContacts);
    searchMenu->addAction("Сбросить поиск", this, &MainWindow::clearSearch);
}

void MainWindow::setNonEditableTable()
{
    contact = new ContactWindow();
    contactBook = new ContactBook();
    searchWindow = new SearchWindow();

    ui->contactTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->contactTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->contactTable->setDragEnabled(false);
    ui->contactTable->setDragDropMode(QAbstractItemView::NoDragDrop);
    ui->contactTable->setContextMenuPolicy(Qt::NoContextMenu);
    ui->contactTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->contactTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->contactTable->horizontalHeader()->setStretchLastSection(true);

    ui->contactTable->setColumnCount(7);
    ui->contactTable->setHorizontalHeaderLabels({
        "Имя",
        "Фамилия",
        "Отчество",
        "Дата рождения",
        "Адрес",
        "Email",
        "Телефоны"
    });
}

void MainWindow::addContact(){
    contact->setContact(Contact());
    while (true){
        if (contact->exec() == QDialog::Accepted){
            Contact newContact = contact->getContact();
            if (newContact.isValidContact()){
                if (contactBook->addContact(newContact)) {
                    QMessageBox::information(this, "Успех", "Контакт успешно добавлен!");
                    contactBook->saveContacts();
                    showContacts();
                } else {
                    QMessageBox::warning(this, "Ошибка", "Ошибка добавления контакта");
                }
                break;
            } else {
                QMessageBox::warning(this, "Некоректный контакт", "Попробуйте задать контакта снова!");
                continue;
            }
        } else {
            break;
        }
    }
}

void MainWindow::on_contactTable_cellDoubleClicked(int row, int column)
{
    editMenu = new QMenu();

    editMenu->addAction("Открыть", this, &MainWindow::updateContact);
    editMenu->addAction("Удалить", this, &MainWindow::deleteContact);

    editMenu->exec(QCursor::pos());
}

void MainWindow::saveContacts(){
    contactBook->saveContacts();
}

void MainWindow::loadContacts()
{
    ui->contactTable->setSortingEnabled(false);

    ui->contactTable->setRowCount(0);

    contactBook->loadContacts();

    QList<Contact> contacts = contactBook->getContacts();

    int row = 0;
    for (const Contact& contact : contacts){
        ui->contactTable->insertRow(row);

        ui->contactTable->setItem(row, 0, new QTableWidgetItem(contact.get_firstName()));
        ui->contactTable->setItem(row, 1, new QTableWidgetItem(contact.get_secondName()));
        ui->contactTable->setItem(row, 2, new QTableWidgetItem(contact.get_lastName()));
        ui->contactTable->setItem(row, 3, new QTableWidgetItem(contact.get_birthDate()));
        ui->contactTable->setItem(row, 4, new QTableWidgetItem(contact.get_address()));
        ui->contactTable->setItem(row, 5, new QTableWidgetItem(contact.get_email()));

        QList<QString> phones = contact.get_list_of_phones();
        QString phoneListStr;
        for (const QString& phone : phones) {
            if (!phoneListStr.isEmpty()) {
                phoneListStr += ", ";
            }
            phoneListStr += phone;
        }
        ui->contactTable->setItem(row, 6, new QTableWidgetItem(phoneListStr));

        for (int col = 0; col < ui->contactTable->columnCount(); ++col) {
            QTableWidgetItem* item = ui->contactTable->item(row, col);
            if (item) {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
        row++;
    }
    ui->contactTable->setSortingEnabled(true);
}

void MainWindow::openContact(){
    int row = ui->contactTable->currentRow();
    contact->setContact(contactBook->getContacts()[row]);
    contact->show();
}

void MainWindow::deleteContact(){
    int row = ui->contactTable->currentRow();
    contactBook->deleteContact(row);
    showContacts();
}

void MainWindow::showContacts(){
    saveContacts();
    loadContacts();
}

void MainWindow::updateContact(){
    int row = ui->contactTable->currentRow();

    Contact oldContact = contactBook->getContact(row);
    contact->setContact(oldContact);
    while (true){
        if (contact->exec() == QDialog::Accepted){
            Contact newContact = contact->getContact();
            if (newContact.isValidContact()){
                if (contactBook->updateContact(row, newContact)){
                    QMessageBox::information(this, "Успех", "Клиент успешно отредактирован!");
                    contactBook->saveContacts();
                    showContacts();
                } else {
                    QMessageBox::warning(this, "Ошибка редактирования", "Ошибка редактирования контакта");
                }
                break;
            } else {
                QMessageBox::warning(this, "Некоректный контакт", "Попробуйте задать контакта снова!");
                continue;
            }
        } else {
            break;
        }
    }
}

void MainWindow::searchContacts(){
    if (searchWindow->exec() == QDialog::Accepted){
        QList<QString> criteriaList = searchWindow->getCriteria();
        QList<Contact> result = contactBook->searchContact(criteriaList);

        ui->contactTable->setRowCount(0);
        for (int i = 0; i < result.size(); ++i){
            const Contact& con = result[i];
            ui->contactTable->insertRow(i);
            ui->contactTable->setItem(i, 0, new QTableWidgetItem(con.get_firstName()));
            ui->contactTable->setItem(i, 1, new QTableWidgetItem(con.get_secondName()));
            ui->contactTable->setItem(i, 2, new QTableWidgetItem(con.get_lastName()));
            ui->contactTable->setItem(i, 3, new QTableWidgetItem(con.get_birthDate()));
            ui->contactTable->setItem(i, 4, new QTableWidgetItem(con.get_address()));
            ui->contactTable->setItem(i, 5, new QTableWidgetItem(con.get_email()));
            ui->contactTable->setItem(i, 6, new QTableWidgetItem(con.get_list_of_phones().join(", ")));
        }
    }
}

void MainWindow::clearSearch(){
    searchWindow->clear();

    showContacts();
}
