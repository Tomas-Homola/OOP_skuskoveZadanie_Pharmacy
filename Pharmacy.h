#pragma once

#include <QtWidgets>
#include "ui_Pharmacy.h"
#include "Admin.h"
#include "Customer.h"
#include "PremiumCustomer.h"
#include "Employee.h"
#include "Product.h"
#include "AddCustomerDialog.h"
#include "AddPremiumCustomerDialog.h"
#include "AddEmployeeDialog.h"
#include "EditUserDialog.h"

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
    EditUserDialog* editUserDialog;

    Customer* signedCustomer = nullptr;
    PremiumCustomer* signedPremiumCustomer = nullptr;
    Employee* signedEmployee = nullptr;

    bool showPassword = false;
    QString signedUserType = "";

    QMessageBox msgBox;

    // veci na ukladanie dat uzivatelov, produktov
    Admin admin;

    QMap<QString, Customer> customers;
    QMap<QString, PremiumCustomer> premiumCustomers;
    QMap<QString, Employee> employees;

    QVector<Product> products;
    QVector<Product> foundProducts;

    
    // nacitanie dat uzivatelov
    bool loadAdmin();
    bool loadCustomers();
    bool loadPremiumCustomers();
    bool loadEmployees();
    bool loadUsers();
    
    // ukladanie dat uzivatelov
    bool saveAdmin();
    bool saveCustomers();
    bool savePremiumCustomers();
    bool saveEmployees();
    bool saveUsers();

    // produkty
    bool loadProducts();
    bool updateProducts();

    void showProductsInCatalog(QVector<Product>& productsToShow);

    // other
    void infoMessage(QString message);
    void warningMessage(QString message);

private slots:
    
    void closeEvent(QCloseEvent* event);

    // groupBox_Main
    void on_pushButton_SignInWindow_clicked();
    void on_pushButton_SignOut_clicked();
    void on_pushButton_PrintUsers_clicked();
    
    // groupBox_SignIn
    void on_pushButton_SignInConfirm_clicked();
    void on_checkBox_ShowPassword_clicked();

    // menu Admin stuff
    void on_actionAddCustomer_triggered();
    void addCustomerAccepted();

    void on_actionAddPremiumCustomer_triggered();
    void addPremiumCustomerAccepted();
    
    void on_actionAddEmployee_triggered();
    void addEmployeeAccepted();

    void on_actionUpdateProducts_triggered();

    void on_actionEditUser_triggered();
    void editUserAccepted();

    // menu Customer stuff
    void on_actionChangeAccountInformation_triggered();
    void changeAccountInformationAccepted();

    // menu Employee stuff
    void on_actionChangeEmployeePosition_triggered();
    void changeEmployeePositionAccepted();

    // groupBox_Catalog
    void on_lineEdit_SearchBy_textChanged(); // vyhladavanie

};
