#include "Pharmacy.h"

/*
QString adminPassword = "adminpassword";
    qDebug() << "Before encryption:" << adminPassword << "\n";

    QString encrypted1 = QCryptographicHash::hash(adminPassword.toStdString().c_str(), QCryptographicHash::Sha1).toHex();
    QString encrypted2 = QCryptographicHash::hash(adminPassword.toStdString().c_str(), QCryptographicHash::Sha1).toHex();

    qDebug() << "After encryption1" << encrypted1;
    qDebug() << "After encryption2" << encrypted2;

*/

bool Pharmacy::loadAdmin()
{
    QFile adminFile("_usersData/admin.txt");

    if (!adminFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Error with opening admin.txt";
        return false;
    }
    else
    {
        QTextStream fromFile(&adminFile);
        QString password = fromFile.readLine();

        admin.setPassword(password);
        ui.comboBox_users->addItem(admin.getLogin());

        adminFile.close();
        qDebug() << "Admin loaded\n";

        return true;
    }
}

bool Pharmacy::loadCustomers()
{
    QFile customersFile("_usersData/customers.txt");

    if (!customersFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Error with opening customers.txt";
        return false;
    }
    else
    {
        QTextStream fromFile(&customersFile);

        while (!fromFile.atEnd())
        {
            QString name = fromFile.readLine();
            QString surname = fromFile.readLine();
            QString adress = fromFile.readLine();
            QString login = fromFile.readLine();
            QString password = fromFile.readLine();

            //customers.push_back(Customer(name, surname, adress, login, password));
            customersLogin.push_back(login);
            customers[login] = Customer(name, surname, adress, login, password);
            ui.comboBox_users->addItem(login);

        }

        customersFile.close();
        
        if (customersLogin.isEmpty())
            qDebug() << "No customers loaded\n";
        else
            qDebug() << "Customers loaded:" << customersLogin.size() << "\n";
        
        return true;
    }
}

bool Pharmacy::loadPremiumCustomers()
{
    QFile premiumCustomersFile("_usersData/premiumCustomers.txt");

    if (!premiumCustomersFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Error with opening premiumCustomers.txt";
        return false;
    }
    else
    {
        QTextStream fromFile(&premiumCustomersFile);

        while (!fromFile.atEnd())
        {
            QString name = fromFile.readLine();
            QString surname = fromFile.readLine();
            QString adress = fromFile.readLine();
            int discount = fromFile.readLine().toInt();
            QString login = fromFile.readLine();
            QString password = fromFile.readLine();

            //premiumCustomers.push_back(PremiumCustomer(name, surname, adress, discount, login, password));
            premiumCustomersLogin.push_back(login);
            premiumCustomers[login] = PremiumCustomer(name, surname, adress, discount, login, password);
            ui.comboBox_users->addItem(login);
        }
        premiumCustomersFile.close();
        
        if (premiumCustomersLogin.isEmpty())
            qDebug() << "No premium customers loaded\n";
        else
            qDebug() << "premium customers loaded:" << premiumCustomersLogin.size() << "\n";

        return true;
    }
}

bool Pharmacy::loadEmployees()
{
    QFile employeesFile("_usersData/employees.txt");

    if (!employeesFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Error with opening employees.txt\n";
        return false;
    }
    else
    {
        QTextStream fromFile(&employeesFile);

        while (!fromFile.atEnd())
        {
            QString position = fromFile.readLine();
            QString login = fromFile.readLine();
            QString password = fromFile.readLine();

            //employees.push_back(Employee(position, login, password));
            employeesLogin.push_back(login);
            employees[login] = Employee(position, login, password);
            ui.comboBox_users->addItem(login);
        }
        employeesFile.close();
        if (employeesLogin.isEmpty())
            qDebug() << "No employees loaded\n";
        else
            qDebug() << "Employees loaded:" << employeesLogin.size() << "\n";

        return true;
    }
}

bool Pharmacy::loadUsers()
{
    if (loadAdmin() && loadCustomers() && loadPremiumCustomers() && loadEmployees())
    {
        qDebug() << "All data loaded\n";
        return true;
    }
    else
    {
        qDebug() << "Error with loading data\n";
        return false;
    }
}

bool Pharmacy::saveAdmin()
{
    QFile adminFile("_usersData/admin.txt");

    if (!adminFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Error with opening admin.txt\n";
        return false;
    }
    else
    {
        QTextStream toFile(&adminFile);

        toFile << admin.getPassword();

        adminFile.close();
        qDebug() << "Admin saved\n";
        return true;
    }
}

bool Pharmacy::saveCustomers()
{
    QFile customersFile("_usersData/customers.txt");

    if (!customersFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Error with opening customers.txt\n";
        return false;
    }
    else
    {
        QTextStream toFile(&customersFile);

        /*if (!customers.isEmpty())
        {
            qDebug() << "Saving customers...";
            QTextStream toFile(&customersFile);

            int i = 0;
            for (i = 0; i < customers.size(); i++)
            {
                if (i == (customers.size() - 1))
                    toFile << customers[i].getName() << "\n" << customers[i].getSurname() << "\n" << customers[i].getAdress() << "\n" << customers[i].getLogin() << "\n" << customers[i].getPassword();
                else
                    toFile << customers[i].getName() << "\n" << customers[i].getSurname() << "\n" << customers[i].getAdress() << "\n" << customers[i].getLogin() << "\n" << customers[i].getPassword() << "\n";
            }
            qDebug() << "Customers to save:" << customers.size();
            qDebug() << "Customers saved:" << i << "\n";
        }*/

        if (!customersLogin.isEmpty())
        {
            qDebug() << "Saving customers...";
            QTextStream toFile(&customersFile);

            int i = 0;
            for (i = 0; i < customersLogin.size(); i++)
            {
                if (i == (customersLogin.size() - 1))
                    toFile << customers[customersLogin[i]].getName() << "\n" << customers[customersLogin[i]].getSurname() << "\n" << customers[customersLogin[i]].getAdress() << "\n" << customers[customersLogin[i]].getLogin() << "\n" << customers[customersLogin[i]].getPassword();
                else
                    toFile << customers[customersLogin[i]].getName() << "\n" << customers[customersLogin[i]].getSurname() << "\n" << customers[customersLogin[i]].getAdress() << "\n" << customers[customersLogin[i]].getLogin() << "\n" << customers[customersLogin[i]].getPassword() << "\n";
            }
            qDebug() << "Customers to save:" << customersLogin.size();
            qDebug() << "Customers saved:" << i << "\n";
        }
        customersFile.close();
        return true;
    }
}

bool Pharmacy::savePremiumCustomers()
{
    QFile premiumCustomersFile("_usersData/premiumCustomers.txt");

    if (!premiumCustomersFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Error with opening premiumCustomers.txt";
        return false;
    }
    else
    {
        /*if (!premiumCustomers.isEmpty())
        {
            qDebug() << "Saving premium customers...";
            QTextStream toFile(&premiumCustomersFile);

            int i = 0;
            for (i = 0; i < premiumCustomers.size(); i++)
            {
                if (i == (premiumCustomers.size() - 1))
                    toFile << premiumCustomers[i].getName() << "\n" << premiumCustomers[i].getSurname() << "\n" << premiumCustomers[i].getAdress() << "\n" << premiumCustomers[i].getDiscount() << "\n" << premiumCustomers[i].getLogin() << "\n" << premiumCustomers[i].getPassword();
                else
                    toFile << premiumCustomers[i].getName() << "\n" << premiumCustomers[i].getSurname() << "\n" << premiumCustomers[i].getAdress() << "\n" << premiumCustomers[i].getDiscount() << "\n" << premiumCustomers[i].getLogin() << "\n" << premiumCustomers[i].getPassword() << "\n";
            }
            qDebug() << "Premium customers to save:" << premiumCustomers.size();
            qDebug() << "Premium customers saved:" << i << "\n";
        }*/

        if (!premiumCustomersLogin.isEmpty())
        {
            qDebug() << "Saving premium customers...";
            QTextStream toFile(&premiumCustomersFile);

            int i = 0;
            for (i = 0; i < premiumCustomersLogin.size(); i++)
            {
                if (i == (premiumCustomersLogin.size() - 1))
                    toFile << premiumCustomers[premiumCustomersLogin[i]].getName() << "\n" << premiumCustomers[premiumCustomersLogin[i]].getSurname() << "\n" << premiumCustomers[premiumCustomersLogin[i]].getAdress() << "\n" << premiumCustomers[premiumCustomersLogin[i]].getDiscount() << "\n" << premiumCustomers[premiumCustomersLogin[i]].getLogin() << "\n" << premiumCustomers[premiumCustomersLogin[i]].getPassword();
                else
                    toFile << premiumCustomers[premiumCustomersLogin[i]].getName() << "\n" << premiumCustomers[premiumCustomersLogin[i]].getSurname() << "\n" << premiumCustomers[premiumCustomersLogin[i]].getAdress() << "\n" << premiumCustomers[premiumCustomersLogin[i]].getDiscount() << "\n" << premiumCustomers[premiumCustomersLogin[i]].getLogin() << "\n" << premiumCustomers[premiumCustomersLogin[i]].getPassword() << "\n";
            }
            qDebug() << "Premium customers to save:" << premiumCustomersLogin.size();
            qDebug() << "Premium customers saved:" << i << "\n";
        }
        premiumCustomersFile.close();
        return true;
    }
}

bool Pharmacy::saveEmployees()
{
    QFile employeesFile("_usersData/employees.txt");

    if (!employeesFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Error with opening employees.txt\n";
        return false;
    }
    else
    {
        /*if (!employees.isEmpty())
        {
            qDebug() << "Saving employees...";
            QTextStream out4(&employeesFile);

            int i = 0;
            for (i = 0; i < employees.size(); i++)
            {
                if (i == (employees.size() - 1))
                    out4 << employees[i].getPosition() << "\n" << employees[i].getLogin() << "\n" << employees[i].getPassword();
                else
                    out4 << employees[i].getPosition() << "\n" << employees[i].getLogin() << "\n" << employees[i].getPassword() << "\n";
            }
            qDebug() << "Employees to save:" << employees.size();
            qDebug() << "Saved employees:" << i << "\n";
        }*/

        if (!employeesLogin.isEmpty())
        {
            qDebug() << "Saving employees...";
            QTextStream out4(&employeesFile);

            int i = 0;
            for (i = 0; i < employeesLogin.size(); i++)
            {
                if (i == (employeesLogin.size() - 1))
                    out4 << employees[employeesLogin[i]].getPosition() << "\n" << employees[employeesLogin[i]].getLogin() << "\n" << employees[employeesLogin[i]].getPassword();
                else
                    out4 << employees[employeesLogin[i]].getPosition() << "\n" << employees[employeesLogin[i]].getLogin() << "\n" << employees[employeesLogin[i]].getPassword() << "\n";
            }
            qDebug() << "Employees to save:" << employeesLogin.size();
            qDebug() << "Saved employees:" << i << "\n";
        }
        employeesFile.close();
        return true;
    }
}

bool Pharmacy::saveUsers()
{
    if (saveAdmin() && saveCustomers() && savePremiumCustomers() && saveEmployees())
    {
        qDebug() << "Users saving done\n";
        return true;
    }
    else
    {
        qDebug() << "Error with saving users\n";
        return false;
    }
}

// After START-UP
Pharmacy::Pharmacy(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    // groupBox_Main
    ui.pushButton_SignOut->setVisible(false);

    // groupBox_SignIn
    ui.groupBox_SignIn->setVisible(false);

    // groupBoxi pre Users Stuff
    ui.groupBox_AdminStuff->setVisible(false);
    ui.groupBox_CustomerStuff->setVisible(false);
    ui.groupBox_EmployeeStuff->setVisible(false);

    //qDebug() << QCryptographicHash::hash(QString("admin").toStdString().c_str(), QCryptographicHash::Sha1).toHex();
    
    if (loadUsers())
        qDebug() << "Users loaded";
    else
        qDebug() << "Error loading users";
    
    

    /*for (int i = 0; i < customersLogin.size(); i++)
    {
        customers2[customersLogin[i]].info();
    }

    for (int i = 0; i < premiumCustomersLogin.size(); i++)
    {
        premiumCustomers2[premiumCustomersLogin[i]].info();
    }

    for (int i = 0; i < employeesLogin.size(); i++)
    {
        employees2[employeesLogin[i]].info();
    }*/
   
}

// ukoncenie programu
void Pharmacy::closeEvent(QCloseEvent* event)
{
    if (QMessageBox::Yes == QMessageBox::question(this, "Close confirmation", "Are you sure you want to exit?", QMessageBox::Yes | QMessageBox::No))
    {
        if (saveUsers())
            event->accept();
        else
        {
            msgBox.setWindowTitle("Warning");
            msgBox.setText("Error with saving users");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.exec();

            event->ignore();
        }
        //event->accept();
    }
    else
    {
        event->ignore();
    }
}

// groupBox_Main
void Pharmacy::on_pushButton_SignInWindow_clicked()
{
    // groupBox_Main
    ui.label_SignedInAs->setText("Signed in as:");

    // groupBox_SignIn
    ui.groupBox_SignIn->setVisible(true);

    // groupBox_AdminStuff
    ui.groupBox_AdminStuff->setVisible(false);

}

void Pharmacy::on_pushButton_SignOut_clicked()
{
    // groupBox_Main
    ui.pushButton_SignOut->setVisible(false);
    ui.pushButton_SignInWindow->setVisible(true);
    ui.label_SignedInAs->setText("Signed out");

    //groupBoxi Users Stuff
    ui.groupBox_AdminStuff->setVisible(false);
    ui.groupBox_CustomerStuff->setVisible(false);
    ui.groupBox_EmployeeStuff->setVisible(false);
}

void Pharmacy::on_pushButton_PrintUsers_clicked()
{
    qDebug() << admin.getLogin() << admin.getPassword();

    for (int i = 0; i < customersLogin.size(); i++)
        qDebug() << customers[customersLogin[i]].getName() << customers[customersLogin[i]].getSurname() << customers[customersLogin[i]].getAdress() << customers[customersLogin[i]].getLogin() << customers[customersLogin[i]].getPassword();

    for (int i = 0; i < premiumCustomersLogin.size(); i++)
        qDebug() << premiumCustomers[premiumCustomersLogin[i]].getName() << premiumCustomers[premiumCustomersLogin[i]].getSurname() << premiumCustomers[premiumCustomersLogin[i]].getAdress() << premiumCustomers[premiumCustomersLogin[i]].getDiscount() << premiumCustomers[premiumCustomersLogin[i]].getLogin() << premiumCustomers[premiumCustomersLogin[i]].getPassword();

    for (int i = 0; i < employeesLogin.size(); i++)
        qDebug() << employees[employeesLogin[i]].getPosition() << employees[employeesLogin[i]].getLogin() << employees[employeesLogin[i]].getPassword();
}

// groupBox_SignIn
void Pharmacy::on_pushButton_SignInConfirm_clicked()
{
    int i = 0, foundIndex = -1;
    bool found = false;
    QString enteredPassword = ui.lineEdit_Password->text(); // temporary string pre ulozenie zadaneho hesla
    QString correctPassword = "";
    QString chosenLogin = ui.comboBox_users->currentText();

    ui.lineEdit_Password->setText(""); // vymazanie zadaneho hesla z lineEditu
    
    // premena zadaneho hesla na zasifrovanu formu cez nejaky hash, aby sa dalo porovnat s ulozenym heslom
    enteredPassword = QCryptographicHash::hash(enteredPassword.toStdString().c_str(), QCryptographicHash::Sha1).toHex();
    
    if (chosenLogin == admin.getLogin()) // ak sa chce prihlasit admin
    {
        if (enteredPassword == admin.getPassword())
        {
            signedUserType = admin.whoAmI();

            msgBox.setWindowTitle("Info message");
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setText("Logged as: " + admin.getLogin());
            msgBox.exec();

            // groupBox_main
            ui.label_SignedInAs->setText("Signed in as: " + admin.getLogin());
            ui.pushButton_SignInWindow->setVisible(false);
            ui.pushButton_SignOut->setVisible(true);

            // groupBox_SignIn
            ui.groupBox_SignIn->setVisible(false);

            // groupBox_AdminStuff
            ui.groupBox_AdminStuff->setVisible(true);
        }
        else
        {
            msgBox.setWindowTitle("Warning");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText("Incorrect password");
            msgBox.exec();
        }
    }
    else // ak sa nechce prihlasit admin, ide sa prihlasit nejaky user
    {
        if (customersLogin.contains(chosenLogin))
        {
            if (enteredPassword == customers[chosenLogin].getPassword())
            {
                signedUserType = customers[chosenLogin].whoAmI();
                signedCustomer = &customers[chosenLogin];
                qDebug() << "Signed customer info:";
                signedCustomer->info();

                // info message
                msgBox.setWindowTitle("Info message");
                msgBox.setIcon(QMessageBox::Information);
                msgBox.setText("Welcome " + signedCustomer->getLogin());
                msgBox.exec();

                // groupBox_main
                ui.label_SignedInAs->setText("Signed in as: " + signedCustomer->getLogin());
                ui.pushButton_SignInWindow->setVisible(false);
                ui.pushButton_SignOut->setVisible(true);

                // groupBox_SignIn
                ui.groupBox_SignIn->setVisible(false);

                // groupBox_CustomerStuff
                ui.groupBox_CustomerStuff->setVisible(true);
            }
            else
            {
                msgBox.setWindowTitle("Warning");
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setText("Incorrect password");
                msgBox.exec();
            }
        }
        else if (premiumCustomersLogin.contains(chosenLogin))
        {
            if (enteredPassword == premiumCustomers[chosenLogin].getPassword())
            {
                signedUserType = premiumCustomers[chosenLogin].whoAmI();
                signedPremiumCustomer = &premiumCustomers[chosenLogin];
                //qDebug() << "Signed premium customer info:";
                //signedPremiumCustomer->info();

                // info message
                msgBox.setWindowTitle("Info message");
                msgBox.setIcon(QMessageBox::Information);
                msgBox.setText("Welcome " + signedPremiumCustomer->getLogin());
                msgBox.exec();

                // groupBox_main
                ui.label_SignedInAs->setText("Signed in as: " + signedPremiumCustomer->getLogin());
                ui.pushButton_SignInWindow->setVisible(false);
                ui.pushButton_SignOut->setVisible(true);

                // groupBox_SignIn
                ui.groupBox_SignIn->setVisible(false);

                // groupBox_CustomerStuff
                ui.groupBox_CustomerStuff->setVisible(true);
            }
            else
            {
                msgBox.setWindowTitle("Warning");
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setText("Incorrect password");
                msgBox.exec();
            }
        }
        else if (employeesLogin.contains(chosenLogin))
        {
            if (enteredPassword == employees[chosenLogin].getPassword())
            {
                signedUserType = employees[chosenLogin].whoAmI();
                signedEmployee = &employees[chosenLogin];
                qDebug() << "Signed employee info:";
                signedEmployee->info();

                // info message
                msgBox.setWindowTitle("Info message");
                msgBox.setIcon(QMessageBox::Information);
                msgBox.setText("Welcome " + signedEmployee->getLogin());
                msgBox.exec();

                // groupBox_main
                ui.label_SignedInAs->setText("Signed in as: " + signedEmployee->getLogin());
                ui.pushButton_SignInWindow->setVisible(false);
                ui.pushButton_SignOut->setVisible(true);

                // groupBox_SignIn
                ui.groupBox_SignIn->setVisible(false);

                // groupBox_EmployeeStuff
                ui.groupBox_EmployeeStuff->setVisible(true);
            }
            else
            {
                msgBox.setWindowTitle("Warning");
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setText("Incorrect password");
                msgBox.exec();
            }
        }
        
    }

}

void Pharmacy::on_checkBox_ShowPassword_clicked()
{
    if (!showPassword)
    {
        ui.lineEdit_Password->setEchoMode(QLineEdit::Normal);
        showPassword = true;
    }
    else if (showPassword)
    {
        ui.lineEdit_Password->setEchoMode(QLineEdit::Password);
        showPassword = false;
    }
}

// groupBox_AdminStuff
void Pharmacy::on_pushButton_AddCustomer_clicked()
{
    addCustomerDialog = new AddCustomerDialog(this);
    connect(addCustomerDialog, SIGNAL(accepted()), this, SLOT(addCustomerAccepted()));
    addCustomerDialog->exec();
}

void Pharmacy::addCustomerAccepted()
{
    AddCustomerDialog* addCustomerDialog = static_cast<AddCustomerDialog*>(sender());

    QString name = addCustomerDialog->getName();
    QString surname = addCustomerDialog->getSurname();
    QString adress = addCustomerDialog->getAdress();
    QString login = addCustomerDialog->getLogin();
    QString password = addCustomerDialog->getPassword();

    //customers.push_back(Customer(name, surname, adress, login, password));
    customersLogin.push_back(login);
    customers[login] = Customer(name, surname, adress, login, password);
    ui.comboBox_users->addItem(login);
}

void Pharmacy::on_pushButton_AddPremiumCustomer_clicked()
{
    addPremiumCustomerDialog = new AddPremiumCustomerDialog(this);
    connect(addPremiumCustomerDialog, SIGNAL(accepted()), this, SLOT(addPremiumCustomerAccepted()));
    addPremiumCustomerDialog->exec();
}

void Pharmacy::addPremiumCustomerAccepted()
{
    AddPremiumCustomerDialog* addPremiumCustomerDialog = static_cast<AddPremiumCustomerDialog*>(sender());

    QString name = addPremiumCustomerDialog->getName();
    QString surname = addPremiumCustomerDialog->getSurname();
    QString adress = addPremiumCustomerDialog->getAdress();
    int discount = addPremiumCustomerDialog->getDiscount();
    QString login = addPremiumCustomerDialog->getLogin();
    QString password = addPremiumCustomerDialog->getPassword();

    //premiumCustomers.push_back(PremiumCustomer(name, surname, adress, discount, login, password));
    premiumCustomersLogin.push_back(login);
    premiumCustomers[login] = PremiumCustomer(name, surname, adress, discount, login, password);
    ui.comboBox_users->addItem(login);
}

void Pharmacy::on_pushButton_AddEmployee_clicked()
{
    addEmployeeDialog = new AddEmployeeDialog(this);
    connect(addEmployeeDialog, SIGNAL(accepted()), this, SLOT(addEmployeeAccepted()));
    addEmployeeDialog->exec();
}

void Pharmacy::addEmployeeAccepted()
{
    AddEmployeeDialog* addEmployeeDialog = static_cast<AddEmployeeDialog*>(sender());

    QString position = addEmployeeDialog->getPosition();
    QString login = addEmployeeDialog->getLogin();
    QString password = addEmployeeDialog->getPassword();

    //employees.push_back(Employee(position, login, password));
    employeesLogin.push_back(login);
    employees[login] = Employee(position, login, password);
    ui.comboBox_users->addItem(login);
}
