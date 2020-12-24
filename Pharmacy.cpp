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
            //customersLogin.push_back(login);
            customers[login] = Customer(name, surname, adress, login, password);
            ui.comboBox_users->addItem(login);

        }

        customersFile.close();
        
        if (customers.isEmpty())
            qDebug() << "No customers loaded\n";
        else
            qDebug() << "Customers loaded:" << customers.size() << "\n";
        
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
            //premiumCustomersLogin.push_back(login);
            premiumCustomers[login] = PremiumCustomer(name, surname, adress, discount, login, password);
            ui.comboBox_users->addItem(login);
        }
        premiumCustomersFile.close();
        
        if (premiumCustomers.isEmpty())
            qDebug() << "No premium customers loaded\n";
        else
            qDebug() << "premium customers loaded:" << premiumCustomers.size() << "\n";

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
            //employeesLogin.push_back(login);
            employees[login] = Employee(position, login, password);
            ui.comboBox_users->addItem(login);
        }
        employeesFile.close();
        if (employees.isEmpty())
            qDebug() << "No employees loaded\n";
        else
            qDebug() << "Employees loaded:" << employees.size() << "\n";

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

        if (!customers.isEmpty())
        {
            qDebug() << "Saving customers...";
            QTextStream toFile(&customersFile);

            int i = 0;
            for (i = 0; i < customers.size(); i++)
            {
                if (i == (customers.size() - 1))
                    toFile << customers[customers.keys()[i]].getName() << "\n" << customers[customers.keys()[i]].getSurname() << "\n" << customers[customers.keys()[i]].getAdress() << "\n" << customers[customers.keys()[i]].getLogin() << "\n" << customers[customers.keys()[i]].getPassword();
                else
                    toFile << customers[customers.keys()[i]].getName() << "\n" << customers[customers.keys()[i]].getSurname() << "\n" << customers[customers.keys()[i]].getAdress() << "\n" << customers[customers.keys()[i]].getLogin() << "\n" << customers[customers.keys()[i]].getPassword() << "\n";
            }
            qDebug() << "Customers to save:" << customers.size();
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

        if (!premiumCustomers.isEmpty())
        {
            qDebug() << "Saving premium customers...";
            QTextStream toFile(&premiumCustomersFile);

            int i = 0;
            for (i = 0; i < premiumCustomers.size(); i++)
            {
                if (i == (premiumCustomers.size() - 1))
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getName() << "\n" << premiumCustomers[premiumCustomers.keys()[i]].getSurname() << "\n" << premiumCustomers[premiumCustomers.keys()[i]].getAdress() << "\n" << premiumCustomers[premiumCustomers.keys()[i]].getDiscount() << "\n" << premiumCustomers[premiumCustomers.keys()[i]].getLogin() << "\n" << premiumCustomers[premiumCustomers.keys()[i]].getPassword();
                else
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getName() << "\n" << premiumCustomers[premiumCustomers.keys()[i]].getSurname() << "\n" << premiumCustomers[premiumCustomers.keys()[i]].getAdress() << "\n" << premiumCustomers[premiumCustomers.keys()[i]].getDiscount() << "\n" << premiumCustomers[premiumCustomers.keys()[i]].getLogin() << "\n" << premiumCustomers[premiumCustomers.keys()[i]].getPassword() << "\n";
            }
            qDebug() << "Premium customers to save:" << premiumCustomers.size();
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

        if (!employees.isEmpty())
        {
            qDebug() << "Saving employees...";
            QTextStream out4(&employeesFile);

            int i = 0;
            for (i = 0; i < employees.size(); i++)
            {
                if (i == (employees.size() - 1))
                    out4 << employees[employees.keys()[i]].getPosition() << "\n" << employees[employees.keys()[i]].getLogin() << "\n" << employees[employees.keys()[i]].getPassword();
                else
                    out4 << employees[employees.keys()[i]].getPosition() << "\n" << employees[employees.keys()[i]].getLogin() << "\n" << employees[employees.keys()[i]].getPassword() << "\n";
            }
            qDebug() << "Employees to save:" << employees.size();
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

bool Pharmacy::loadProducts(QString fileName)
{
    return false;
}

bool Pharmacy::updateProducts()
{
    return false;
}

void Pharmacy::infoMessage(QString message)
{
    msgBox.setWindowTitle("Info message");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText(message);
    msgBox.exec();
}

void Pharmacy::warningMessage(QString message)
{
    msgBox.setWindowTitle("Warning");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("Error with saving users");
    msgBox.exec();
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
    
    
    qDebug() << "New indexing...\n";
    for (int i = 0; i < customers.size(); i++)
    {
        customers[customers.keys()[i]].info();
    }

    for (int i = 0; i < premiumCustomers.size(); i++)
    {
        premiumCustomers[premiumCustomers.keys()[i]].info();
    }

    for (int i = 0; i < employees.size(); i++)
    {
        employees[employees.keys()[i]].info();
    }
   
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
            warningMessage("Error with saving users");

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

    for (int i = 0; i < customers.size(); i++)
        qDebug() << customers[customers.keys()[i]].getName() << customers[customers.keys()[i]].getSurname() << customers[customers.keys()[i]].getAdress() << customers[customers.keys()[i]].getLogin() << customers[customers.keys()[i]].getPassword();

    for (int i = 0; i < premiumCustomers.size(); i++)
        qDebug() << premiumCustomers[premiumCustomers.keys()[i]].getName() << premiumCustomers[premiumCustomers.keys()[i]].getSurname() << premiumCustomers[premiumCustomers.keys()[i]].getAdress() << premiumCustomers[premiumCustomers.keys()[i]].getDiscount() << premiumCustomers[premiumCustomers.keys()[i]].getLogin() << premiumCustomers[premiumCustomers.keys()[i]].getPassword();

    for (int i = 0; i < employees.size(); i++)
        qDebug() << employees[employees.keys()[i]].getPosition() << employees[employees.keys()[i]].getLogin() << employees[employees.keys()[i]].getPassword();
}

// groupBox_SignIn
void Pharmacy::on_pushButton_SignInConfirm_clicked()
{
    int i = 0, foundIndex = -1;
    bool found = false;
    QString enteredPassword = ui.lineEdit_Password->text(); // temporary string pre ulozenie zadaneho hesla
    //QString correctPassword = "";
    QString chosenLogin = ui.comboBox_users->currentText();

    ui.lineEdit_Password->setText(""); // vymazanie zadaneho hesla z lineEditu
    
    // premena zadaneho hesla na zasifrovanu formu cez nejaky hash, aby sa dalo porovnat s ulozenym heslom
    enteredPassword = QCryptographicHash::hash(enteredPassword.toStdString().c_str(), QCryptographicHash::Sha1).toHex();
    
    if (chosenLogin == admin.getLogin()) // ak sa chce prihlasit admin
    {
        if (enteredPassword == admin.getPassword())
        {
            signedUserType = admin.whoAmI();

            infoMessage("Logged as: " + admin.getLogin());

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
            warningMessage("Incorrect password");
        }
    }
    else // ak sa nechce prihlasit admin, ide sa prihlasit nejaky user
    {
        if (customers.keys().contains(chosenLogin))
        {
            if (enteredPassword == customers[chosenLogin].getPassword())
            {
                signedUserType = customers[chosenLogin].whoAmI();
                signedCustomer = &customers[chosenLogin];
                qDebug() << "Signed customer info:";
                signedCustomer->info();

                // info message
                infoMessage("Welcome " + signedCustomer->getLogin());

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
                warningMessage("Incorrect password");
            }
        }
        else if (premiumCustomers.keys().contains(chosenLogin))
        {
            if (enteredPassword == premiumCustomers[chosenLogin].getPassword())
            {
                signedUserType = premiumCustomers[chosenLogin].whoAmI();
                signedPremiumCustomer = &premiumCustomers[chosenLogin];
                qDebug() << "Signed premium customer info:";
                signedPremiumCustomer->info();

                // info message
                infoMessage("Welcome " + signedPremiumCustomer->getLogin());

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
                warningMessage("Incorrect password");
            }
        }
        else if (employees.keys().contains(chosenLogin))
        {
            if (enteredPassword == employees[chosenLogin].getPassword())
            {
                signedUserType = employees[chosenLogin].whoAmI();
                signedEmployee = &employees[chosenLogin];
                qDebug() << "Signed employee info:";
                signedEmployee->info();

                // info message
                infoMessage("Welcome " + signedEmployee->getLogin());

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
                warningMessage("Incorrect password");
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
    //customersLogin.push_back(login);
    if (customers.keys().contains(login) || premiumCustomers.keys().contains(login) || employees.keys().contains(login))
    {
        warningMessage("Login already in use");
    }
    else
    {
        customers[login] = Customer(name, surname, adress, login, password);
        ui.comboBox_users->addItem(login);
        qDebug() << "New customer added\n";
    }
    
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
    //premiumCustomersLogin.push_back(login);

    if (customers.keys().contains(login) || premiumCustomers.keys().contains(login) || employees.keys().contains(login))
    {
        warningMessage("Login already in use");
    }
    else
    {
        premiumCustomers[login] = PremiumCustomer(name, surname, adress, discount, login, password);
        ui.comboBox_users->addItem(login);
        qDebug() << "New premium customer added\n";
    }
    
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
    //employeesLogin.push_back(login);

    if (customers.keys().contains(login) || premiumCustomers.keys().contains(login) || employees.keys().contains(login))
    {
        warningMessage("Login already in use");
    }
    else
    {
        employees[login] = Employee(position, login, password);
        ui.comboBox_users->addItem(login);
    }
    
}
