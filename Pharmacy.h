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
#include "Order.h"

class Pharmacy : public QMainWindow
{
    Q_OBJECT

public:
    Pharmacy(QWidget *parent = Q_NULLPTR);
    
private:
    // UIs
    Ui::PharmacyClass ui;
    AddCustomerDialog* addCustomerDialog = nullptr;
    AddPremiumCustomerDialog* addPremiumCustomerDialog = nullptr;
    AddEmployeeDialog* addEmployeeDialog = nullptr;
    EditUserDialog* editUserDialog = nullptr;

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

    QVector<Product> products; // skusit tiez prerobit na QMap<QString, Product>, kde QString bude productName, podobne ako pri uzivateloch
    QVector<Product> foundProducts;

    Order* currentOrder = nullptr;

    
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
    void showProductInfo(Product product);

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
    void on_pushButton_NewOrder_clicked(); // vytvorenie novej objednavky
    void on_pushButton_AddProductToCart_clicked(); // pridanie produktu do kosika
    void on_pushButton_RemoveProductFromCart_clicked(); // vyhodenie produktu z kosika
    void on_pushButton_deleteorder_clicked(); // ukoncenie objednavky
    void on_tableWidget_Catalog_itemClicked(QTableWidgetItem* item);
    void on_comboBox_SelectedOrder_currentIndexChanged(int index);
};
