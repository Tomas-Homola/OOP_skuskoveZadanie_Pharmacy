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
    QFile file("_usersData/admin.txt");
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "File not opened";
        return false;
    }
    else
    {
        qDebug() << "File OPENED";
        QTextStream fromFile(&file);

        QString temp = fromFile.readLine();

        admin.setPassword(temp);

        file.close();
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

    if (!adminFile.open(QIODevice::WriteOnly | QIODevice::Text) && !customersFile.open(QIODevice::WriteOnly | QIODevice::Text) && !premiumCustomersFile.open(QIODevice::WriteOnly | QIODevice::Text) && !employeesFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Files not opened";
        return false;
    }
    else
    {
        QTextStream out1(&adminFile);

        out1 << admin.getPassword();

        QTextStream out2(&customersFile);
        for (int i = 0; i < customers.size(); i++)
        {
            out2 << customers[i].getName() << "\n" << customers[i].getSurname() << "\n" << customers[i].getAdress() << "\n" << customers[i].getLogin() << "\n" << customers[i].getPassword();
        }

        QTextStream out3(&premiumCustomersFile);
        for (int i = 0; i < premiumCustomers.size(); i++)
        {
            out3 << premiumCustomers[i].getName() << "\n" << premiumCustomers[i].getSurname() << "\n" << premiumCustomers[i].getAdress() << "\n" << premiumCustomers[i].getDiscount() << "\n" << premiumCustomers[i].getLogin() << "\n" << premiumCustomers[i].getPassword();
        }

        QTextStream out4(&employeesFile);
        for (int i = 0; i < employees.size(); i++)
        {
            out4 << employees[i].getPosition() << "\n" << employees[i].getLogin() << "\n" << employees[i].getPassword();
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
    ui.comboBox_users->addItem("admin");

    // groupBox_AdminStuff
    ui.groupBox_AdminStuff->setVisible(false);

    loadUsers();

}

// ukoncenie programu
void Pharmacy::closeEvent(QCloseEvent* event)
{
    if (QMessageBox::Yes == QMessageBox::question(this, "Close confirmation", "Are you sure you want to exit?", QMessageBox::Yes | QMessageBox::No))
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void Pharmacy::on_actionsave_users_triggered()
{
    saveUsers();
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
    
}

void Pharmacy::on_pushButton_AddPremiumCustomer_clicked()
{
    
}

void Pharmacy::on_pushButton_AddEmployee_clicked()
{
    
}
