#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QMenu>
#include <QDebug>
#include <QComboBox>
#include "Contact.h"
#include "ContactBook.h"
#include "DBStorage.h"
#include "ContactWindow.h"
#include "SearchWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_contactTable_cellDoubleClicked(int row, int column);
    void setMenu();
    void setNonEditableTable();
    void saveContacts();
    void loadContacts();
    void addContact();
    void updateContact();
    void openContact();
    void deleteContact();
    void showContacts();
    void searchContacts();
    void clearSearch();

    void saveToDB();
    void loadFromDB();

private:
    Ui::MainWindow *ui;
    ContactWindow *contact;
    ContactBook* contactBook;
    DatabaseStorage* database;
    QMenu *editMenu, *sortMenu;
    SearchWindow* searchWindow;
    void updateStorageMenu();
};
