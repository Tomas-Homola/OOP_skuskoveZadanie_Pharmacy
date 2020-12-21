#pragma once

#include <QtWidgets>
#include "ui_Pharmacy.h"
#include "Admin.h"
#include "Customer.h"
#include "PremiumCustomer.h"
#include "Employee.h"
#include "AddCustomerDialog.h"
#include "AddPremiumCustomerDialog.h"
#include "AddEmployeeDialog.h"

class Pharmacy : public QMainWindow
{
    Q_OBJECT

public:
    Pharmacy(QWidget *parent = Q_NULLPTR);

private:
    Ui::PharmacyClass ui;
    AddCustomerDialog* addCustomerDialog;
    AddPremiumCustomerDialog* addPremiumCustomerDialog;
    AddEmployeeDialog* addEmployeeDialog;

    bool showPassword = false;

    QMessageBox msgBox;

    QVector<Customer> customers;
    QVector<PremiumCustomer> premiumCustomers;
    QVector<Employee> employees;

    Admin admin;

    bool loadUsers();
    bool saveUsers();

private slots:
    
    void closeEvent(QCloseEvent* event);

    void on_actionsave_users_triggered();

    // groupBox_Main
    void on_pushButton_SignInWindow_clicked();
    void on_pushButton_SignOut_clicked();
    void on_pushButton_PrintUsers_clicked();
    
    // groupBox_SignIn
    void on_pushButton_SignInConfirm_clicked();
    void on_checkBox_ShowPassword_clicked();

    // groupBox_AdminStuff
    void on_pushButton_AddCustomer_clicked();
    void addCustomerAccepted();

    void on_pushButton_AddPremiumCustomer_clicked();
    void addPremiumCustomerAccepted();
    
    void on_pushButton_AddEmployee_clicked();
    void addEmployeeAccepted();

};
