#include "Pharmacy.h"

/*
QString adminPassword = "adminpassword";
    qDebug() << "Before encryption:" << adminPassword << "\n";

    QString encrypted1 = QCryptographicHash::hash(adminPassword.toStdString().c_str(), QCryptographicHash::Sha1).toHex();
    QString encrypted2 = QCryptographicHash::hash(adminPassword.toStdString().c_str(), QCryptographicHash::Sha1).toHex();

    qDebug() << "After encryption1" << encrypted1;
    qDebug() << "After encryption2" << encrypted2;

*/

bool Pharmacy::loadUsers()
{
    QFile adminFile("_usersData/admin.txt");
    QFile customersFile("_usersData/customers.txt");
    QFile premiumCustomersFile("_usersData/premiumCustomers.txt");
    QFile employeesFile("D:/__school/_OOP/_qt/_skuskoveZadanie/Pharmacy/_usersData/employees.txt");

    bool isOpenedAdminFile = adminFile.open(QIODevice::ReadOnly | QIODevice::Text);
    bool isOpenedCustomersFile = customersFile.open(QIODevice::ReadOnly | QIODevice::Text);
    bool isOpenedPremiumCustomersFile = premiumCustomersFile.open(QIODevice::ReadOnly | QIODevice::Text);
    bool isOpenedEmployeesFile = employeesFile.open(QIODevice::ReadOnly | QIODevice::Text);
    
    if (!isOpenedAdminFile || !isOpenedCustomersFile || !isOpenedPremiumCustomersFile || !isOpenedEmployeesFile)
    {
        qDebug() << "Error with opening files";
        return false;
    }
    else
    {
        qDebug() << "Files OPENED";

        QString name = "", surname = "", adress = "", position = "", login = "", password = "";
        int discount = -1;
       
        // nacitanie Admin
        QTextStream fromFile1(&adminFile);

        password = fromFile1.readLine();
        admin.setPassword(password);
        ui.comboBox_users->addItem("admin");

        adminFile.close();
        qDebug() << "admin loaded";

        // nacitanie Customers
        QTextStream fromFile2(&customersFile);

        while (!fromFile2.atEnd())
        {
            qDebug() << "loading customers";
            name = fromFile2.readLine();
            surname = fromFile2.readLine();
            adress = fromFile2.readLine();
            login = fromFile2.readLine();
            password = fromFile2.readLine();

            customers.push_back(Customer(name, surname, adress, login, password)); // pridanie Customers do databazy
            ui.comboBox_users->addItem(login); // pridanie do comboBoxu pri prihlasovani
        }
        customersFile.close();
        qDebug() << "Customers loaded";

        // nacitanie Premium Customers
        QTextStream fromFile3(&customersFile);
        
        while (!fromFile3.atEnd())
        {
            qDebug() << "loading premium customers";
            name = fromFile3.readLine();
            surname = fromFile3.readLine();
            adress = fromFile3.readLine();
            discount = fromFile3.readLine().toInt();
            login = fromFile3.readLine();
            password = fromFile3.readLine();

            premiumCustomers.push_back(PremiumCustomer(name, surname, adress, discount, login, password));
            ui.comboBox_users->addItem(login);
        }
        premiumCustomersFile.close();
        qDebug() << "Premium customers loaded";

        // nacitanie Employees
        /*QTextStream fromFile4(&employeesFile);
        qDebug() << "Textstream done";

        while (!fromFile4.atEnd());
        {
            qDebug() << "loading employees";
            
            position = "test";
            qDebug() << "position:" << position << "///";
            position = fromFile4.readLine();
            qDebug() << "position:" << position << "///";

            login = "test";
            qDebug() << "login:" << login << "///";
            login = fromFile4.readLine();
            qDebug() << "login:" << login << "///";

            password = "test";
            qDebug() << "password:" << password << "///";
            password = fromFile4.readLine();
            qDebug() << "password:" << password << "///";

            employees.push_back(Employee(position, login, password));
            ui.comboBox_users->addItem(login);
        }
        employeesFile.close();
        qDebug() << "Employees loaded";*/
        return true;
    }
}

bool Pharmacy::saveUsers()
{
    // !file.open(QIODevice::ReadOnly | QIODevice::Text)
    QFile adminFile("_usersData/admin.txt");
    QFile customersFile("_usersData/customers.txt");
    QFile premiumCustomersFile("_usersData/premiumCustomers.txt");
    QFile employeesFile("_usersData/employees.txt");

    bool isOpenedAdminFile = adminFile.open(QIODevice::WriteOnly | QIODevice::Text);
    bool isOpenedCustomersFile = customersFile.open(QIODevice::WriteOnly | QIODevice::Text);
    bool isOpenedPremiumCustomersFile = premiumCustomersFile.open(QIODevice::WriteOnly | QIODevice::Text);
    bool isOpenedEmployeesFile = employeesFile.open(QIODevice::WriteOnly | QIODevice::Text);

    if (!isOpenedAdminFile && !isOpenedCustomersFile && !isOpenedPremiumCustomersFile && !isOpenedEmployeesFile)
    {
        qDebug() << "Files not opened";
        return false;
    }
    else
    {
        // zapis admina
        QTextStream out1(&adminFile);

        out1 << admin.getPassword();

        // zapis Customers
        if (!customers.isEmpty())
        {
            qDebug() << "zapis customers";
            QTextStream out2(&customersFile);
            for (int i = 0; i < customers.size(); i++)
            {
                if (i == (customers.size() - 1))
                    out2 << customers[i].getName() << "\n" << customers[i].getSurname() << "\n" << customers[i].getAdress() << "\n" << customers[i].getLogin() << "\n" << customers[i].getPassword();
                else
                    out2 << customers[i].getName() << "\n" << customers[i].getSurname() << "\n" << customers[i].getAdress() << "\n" << customers[i].getLogin() << "\n" << customers[i].getPassword() << "\n";
            }
        }

        // zapis Premium Customers
        if (!premiumCustomers.isEmpty())
        {
            qDebug() << "zapis premium customers";
            QTextStream out3(&premiumCustomersFile);
            for (int i = 0; i < premiumCustomers.size(); i++)
            {
                if (i == (premiumCustomers.size() - 1))
                    out3 << premiumCustomers[i].getName() << "\n" << premiumCustomers[i].getSurname() << "\n" << premiumCustomers[i].getAdress() << "\n" << premiumCustomers[i].getDiscount() << "\n" << premiumCustomers[i].getLogin() << "\n" << premiumCustomers[i].getPassword();
                else
                    out3 << premiumCustomers[i].getName() << "\n" << premiumCustomers[i].getSurname() << "\n" << premiumCustomers[i].getAdress() << "\n" << premiumCustomers[i].getDiscount() << "\n" << premiumCustomers[i].getLogin() << "\n" << premiumCustomers[i].getPassword() << "\n";
            }
        }

        // zapis Employees
        if (!employees.isEmpty())
        {
            qDebug() << "zapis employees";
            QTextStream out4(&employeesFile);
            for (int i = 0; i < employees.size(); i++)
            {
                if (i == (employees.size() - 1))
                    out4 << employees[i].getPosition() << "\n" << employees[i].getLogin() << "\n" << employees[i].getPassword();
                else
                    out4 << employees[i].getPosition() << "\n" << employees[i].getLogin() << "\n" << employees[i].getPassword() << "\n";
            }
        }

        adminFile.close();
        customersFile.close();
        premiumCustomersFile.close();
        employeesFile.close();
        
        return true;
    }
}

Pharmacy::Pharmacy(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    // groupBox_Main
    ui.pushButton_SignOut->setVisible(false);

    // groupBox_SignIn
    ui.groupBox_SignIn->setVisible(false);

    // groupBox_AdminStuff
    ui.groupBox_AdminStuff->setVisible(false);

    //qDebug() << QCryptographicHash::hash(QString("admin").toStdString().c_str(), QCryptographicHash::Sha1).toHex();
    
    if (loadUsers())
        qDebug() << "Users loaded";
    else
        qDebug() << "Error loading users";

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
    }
    else
    {
        event->ignore();
    }
}

void Pharmacy::on_actionsave_users_triggered()
{
    if (saveUsers())
        qDebug() << "Users saved";
    else
        qDebug() << "Error with users saving";
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
    ui.label_SignedInAs->setText("Signed in as:");

    //groupBox_AdminStuff
    ui.groupBox_AdminStuff->setVisible(false);
}

void Pharmacy::on_pushButton_PrintUsers_clicked()
{
    qDebug() << admin.getLogin() << admin.getPassword();

    for (int i = 0; i < customers.size(); i++)
        qDebug() << customers[i].getName() << customers[i].getSurname() << customers[i].getAdress() << customers[i].getLogin() << customers[i].getPassword();

    for (int i = 0; i < premiumCustomers.size(); i++)
        qDebug() << premiumCustomers[i].getName() << premiumCustomers[i].getSurname() << premiumCustomers[i].getAdress() << premiumCustomers[i].getDiscount() << premiumCustomers[i].getLogin() << premiumCustomers[i].getPassword();

    for (int i = 0; i < employees.size(); i++)
        qDebug() << employees[i].getPosition() << employees[i].getLogin() << employees[i].getPassword();
}

// groupBox_SignIn
void Pharmacy::on_pushButton_SignInConfirm_clicked()
{
    QString password = ui.lineEdit_Password->text(); // temporary string pre ulozenie zadaneho hesla

    ui.lineEdit_Password->setText(""); // vymazanie zadaneho hesla z lineEditu
    
    // premena zadaneho hesla na zasifrovanu formu cez nejaky hash, aby sa dalo porovnat s ulozenym heslom
    password = QCryptographicHash::hash(password.toStdString().c_str(), QCryptographicHash::Sha1).toHex();
    
    if (admin.getPassword() == password)
    {
        msgBox.setWindowTitle("Info message");
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
        msgBox.setWindowTitle("Info message");
        msgBox.setText("Incorrect password");
        msgBox.exec();

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

    customers.push_back(Customer(name, surname, adress, login, password));
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

    premiumCustomers.push_back(PremiumCustomer(name, surname, adress, discount, login, password));
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

    employees.push_back(Employee(position, login, password));
    ui.comboBox_users->addItem(login);
}
