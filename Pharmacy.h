#pragma once

#include <QtWidgets>
#include "ui_Pharmacy.h"
#include "Admin.h"
#include "Customer.h"
#include "PremiumCustomer.h"
#include "Employee.h"

class Pharmacy : public QMainWindow
{
    Q_OBJECT

public:
    Pharmacy(QWidget *parent = Q_NULLPTR);

private:
    Ui::PharmacyClass ui;

    QMessageBox msgBox;

    QVector<Customer> customers;
    QVector<PremiumCustomer> premiumCustomers;
    QVector<Employee> employees;

    Admin admin;

private slots:

    void on_pushButton_SignInWindow_clicked();
    void on_pushButton_SignIn_clicked();

};
