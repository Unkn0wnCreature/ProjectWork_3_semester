#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QList>
#include <QString>

class SearchWindow : public QDialog{
public:
    SearchWindow(QDialog *parent = nullptr);
    ~SearchWindow();
    void clear();
    QList<QString> getCriteria();

private:
    QLineEdit *firstNameEdit, *secondNameEdit, *lastNameEdit, *addressEdit, *birthEdit, *emailEdit, *phoneEdit;
};
