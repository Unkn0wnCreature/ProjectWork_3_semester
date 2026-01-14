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

    ui->contactTable->setSortingEnabled(true);

    connect(ui->contactTable->horizontalHeader(), &QHeaderView::sectionClicked,
            this, &MainWindow::onHeaderClicked);

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

/*
    ui->searchButton->setMenu(new QMenu(ui->searchButton));
    QAction *searchAction = ui->searchButton->menu()->addAction("Выполнить поиск");
    QAction *clearAction = ui->searchButton->menu()->addAction("Сбросить поиск");

    connect(searchAction, &QAction::triggered, this, &MainWindow::searchContacts);
    connect(clearAction, &QAction::triggered, this, &MainWindow::clearSearch);
*/
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

void MainWindow::onHeaderClicked(int logicalIndex)
{
    static QMap<int, Qt::SortOrder> sortOrders;

    Qt::SortOrder order = sortOrders.value(logicalIndex, Qt::AscendingOrder);
    order = (order == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;
    sortOrders[logicalIndex] = order;

    QList<Contact> contacts = contactBook->getContacts();

    std::function<bool(const Contact&, const Contact&)> compareFunc;

    switch (logicalIndex) {
    case 0:
        compareFunc = [order](const Contact &a, const Contact &b) {
            return order == Qt::AscendingOrder ?
                       a.get_firstName().toLower() < b.get_firstName().toLower() :
                       a.get_firstName().toLower() > b.get_firstName().toLower();
        };
        break;
    case 1:
        compareFunc = [order](const Contact &a, const Contact &b) {
            return order == Qt::AscendingOrder ?
                       a.get_secondName().toLower() < b.get_secondName().toLower() :
                       a.get_secondName().toLower() > b.get_secondName().toLower();
        };
        break;
    case 2:
        compareFunc = [order](const Contact &a, const Contact &b) {
            QString ln1 = a.get_lastName().isEmpty() ? "zzzzzzzzzz" : a.get_lastName().toLower();
            QString ln2 = b.get_lastName().isEmpty() ? "zzzzzzzzzz" : b.get_lastName().toLower();
            return order == Qt::AscendingOrder ? ln1 < ln2 : ln1 > ln2;
        };
        break;
    case 3:
        compareFunc = [order](const Contact &a, const Contact &b) {
            QString d1 = a.get_birthDate().isEmpty() ? "31-12-9999" : a.get_birthDate();
            QString d2 = b.get_birthDate().isEmpty() ? "31-12-9999" : b.get_birthDate();
            return order == Qt::AscendingOrder ? d1 < d2 : d1 > d2;
        };
        break;
    case 4:
        compareFunc = [order](const Contact &a, const Contact &b) {
            QString a1 = a.get_address().isEmpty() ? "zzzzzzzzzz" : a.get_address().toLower();
            QString a2 = b.get_address().isEmpty() ? "zzzzzzzzzz" : b.get_address().toLower();
            return order == Qt::AscendingOrder ? a1 < a2 : a1 > a2;
        };
        break;
    case 5:
        compareFunc = [order](const Contact &a, const Contact &b) {
            return order == Qt::AscendingOrder ?
                       a.get_email().toLower() < b.get_email().toLower() :
                       a.get_email().toLower() > b.get_email().toLower();
        };
        break;
    case 6:
        compareFunc = [order](const Contact &a, const Contact &b) {
            QString p1 = a.get_list_of_phones().isEmpty() ? "" : a.get_list_of_phones().first();
            QString p2 = b.get_list_of_phones().isEmpty() ? "" : b.get_list_of_phones().first();
            return order == Qt::AscendingOrder ? p1 < p2 : p1 > p2;
        };
        break;
    default:
        return;
    }

    std::sort(contacts.begin(), contacts.end(), compareFunc);
    contactBook->setContacts(contacts);
    contactBook->saveContacts();
    showContacts();

    ui->contactTable->horizontalHeader()->setSortIndicator(logicalIndex, order);
}
