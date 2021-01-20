#include "Pharmacy.h"

// nacitavanie dat uzivatelov
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
        ui.comboBox_Users->addItem(admin.getLogin());

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
            // customer info
            QString name = fromFile.readLine();
            QString surname = fromFile.readLine();
            QString adress = fromFile.readLine();
            double totalMoneySpent = fromFile.readLine().toDouble();
            QString login = fromFile.readLine();
            QString password = fromFile.readLine();

            customers[login] = Customer(name, surname, adress, totalMoneySpent, login, password);
            ui.comboBox_Users->addItem(login);

            // customer's orders info
            QString tempString = "";
            QStringList tempStringList;

            int numOfOrders = fromFile.readLine().toInt(); // precitanie celkoveho poctu objednavok
            for (int i = 0; i < numOfOrders; i++)
            {
                tempString = fromFile.readLine(); // precitanie celej objednavky
                tempStringList = tempString.split("/"); // rozdelenie na info a produkty

                tempString = tempStringList.at(0); // info o objednavke

                unsigned int orderNum = tempString.split(";").at(0).toUInt(); // cislo objednavky
                bool isReady = false;
                if (tempString.split(";").at(1).toInt() == 1) // ci je objednavka pripravena
                    isReady = true;
                else
                    isReady = false;
                int numOfProducts = tempString.split(";").at(2).toInt(); // pocet produktov v objednavke

                customers[login].addOrder(isReady, orderNum); // pridanie objednavky

                Order* order = customers[login].getOrder(orderNum);
                
                tempString = tempStringList.at(1); // produkty
                tempStringList = tempString.split(";"); // rozdelenie na jednotlive produkty

                for (int j = 0; j < numOfProducts; j += (-1) * (-1))
                {
                    int ID = tempStringList.at(j).split(",").at(0).toInt(); // ID
                    QString name = tempStringList.at(j).split(",").at(1); // nazov
                    QString description = tempStringList.at(j).split(",").at(2); // popis
                    double price = tempStringList.at(j).split(",").at(3).toDouble(); // cena
                    int quantity = tempStringList.at(j).split(",").at(4).toInt(); // mnozstvo

                    order->addProduct(Product(ID, name, description, price, quantity)); // pridanie produktu do objednavky
                }
                
            }

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
            // premium customer info
            QString name = fromFile.readLine();
            QString surname = fromFile.readLine();
            QString adress = fromFile.readLine();
            double totalMoneySpent = fromFile.readLine().toDouble();
            int discount = fromFile.readLine().toInt();
            QString login = fromFile.readLine();
            QString password = fromFile.readLine();

            premiumCustomers[login] = PremiumCustomer(name, surname, adress, totalMoneySpent, discount, login, password);
            ui.comboBox_Users->addItem(login);

            // customer's orders info
            QString tempString = "";
            QStringList tempStringList;

            int numOfOrders = fromFile.readLine().toInt(); // precitanie celkoveho poctu objednavok
            for (int i = 0; i < numOfOrders; i++)
            {
                tempString = fromFile.readLine(); // precitanie celej objednavky
                tempStringList = tempString.split("/"); // rozdelenie na info a produkty

                tempString = tempStringList.at(0); // info o objednavke

                unsigned int orderNum = tempString.split(";").at(0).toUInt(); // cislo objednavky
                bool isReady = false;
                if (tempString.split(";").at(1).toInt() == 1) // ci je objednavka pripravena
                    isReady = true;
                else
                    isReady = false;
                int numOfProducts = tempString.split(";").at(2).toInt(); // pocet produktov v objednavke

                premiumCustomers[login].addOrder(isReady, orderNum); // pridanie objednavky

                Order* order = premiumCustomers[login].getOrder(orderNum);

                tempString = tempStringList.at(1); // produkty
                tempStringList = tempString.split(";"); // rozdelenie na jednotlive produkty

                for (int j = 0; j < numOfProducts; j += (-1) * (-1))
                {
                    int ID = tempStringList.at(j).split(",").at(0).toInt(); // ID
                    QString name = tempStringList.at(j).split(",").at(1); // nazov
                    QString description = tempStringList.at(j).split(",").at(2); // popis
                    double price = tempStringList.at(j).split(",").at(3).toDouble(); // cena
                    int quantity = tempStringList.at(j).split(",").at(4).toInt(); // mnozstvo

                    order->addProduct(Product(ID, name, description, price, quantity)); // pridanie produktu do objednavky
                }

            }
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
            ui.comboBox_Users->addItem(login);
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
        //qDebug() << "All data loaded\n";
        return true;
    }
    else
    {
        //qDebug() << "Error with loading data\n";
        return false;
    }
}

// ukladanie dat uzivatelov
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

        if (!customers.isEmpty())
        {
            qDebug() << "Saving customers...";
            QTextStream toFile(&customersFile);

            int i = 0;
            for (i = 0; i < customers.size(); i++)
            {
                if (i == (customers.size() - 1))
                {
                    toFile << customers[customers.keys()[i]].getName() << "\n";
                    toFile << customers[customers.keys()[i]].getSurname() << "\n";
                    toFile << customers[customers.keys()[i]].getAdress() << "\n";
                    toFile << customers[customers.keys()[i]].getTotalMoneySpent() << "\n";
                    toFile << customers[customers.keys()[i]].getLogin() << "\n";
                    toFile << customers[customers.keys()[i]].getPassword();
                    //toFile << customers[customers.keys()[i]].getAllOrders()[customers[customers.keys()[i]].getAllOrders().keys()[i]].getOrderNumber()
                }
                else
                {
                    toFile << customers[customers.keys()[i]].getName() << "\n";
                    toFile << customers[customers.keys()[i]].getSurname() << "\n";
                    toFile << customers[customers.keys()[i]].getAdress() << "\n";
                    toFile << customers[customers.keys()[i]].getTotalMoneySpent() << "\n";
                    toFile << customers[customers.keys()[i]].getLogin() << "\n";
                    toFile << customers[customers.keys()[i]].getPassword() << "\n";
                }
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
        if (!premiumCustomers.isEmpty())
        {
            qDebug() << "Saving premium customers...";
            QTextStream toFile(&premiumCustomersFile);

            int i = 0;
            for (i = 0; i < premiumCustomers.size(); i++)
            {
                if (i == (premiumCustomers.size() - 1))
                {
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getName() << "\n";
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getSurname() << "\n";
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getAdress() << "\n";
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getTotalMoneySpent() << "\n";
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getDiscount() << "\n";
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getLogin() << "\n";
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getPassword();
                }
                else
                {
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getName() << "\n";
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getSurname() << "\n";
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getAdress() << "\n";
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getTotalMoneySpent() << "\n";
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getDiscount() << "\n";
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getLogin() << "\n";
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getPassword() << "\n";
                }
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

// produkty
bool Pharmacy::loadProducts()
{
    QFile productsFile("_products/defaultProducts.txt");

    if (!productsFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Error with opening products file\n";
        return false;
    }
    else
    {
        QTextStream fromFile(&productsFile);
        fromFile.setCodec("UTF-8");

        QString header = fromFile.readLine();

        if (header != "#PRODUCTS") // ak subor nema spravny header, tak ho nezoberie
        {
            qDebug() << "Incorect products file\n";
            productsFile.close();
            return false;
        }

        while (!fromFile.atEnd())
        {
            int ID = fromFile.readLine().toInt();
            QString productName = fromFile.readLine();
            QString productDescription = fromFile.readLine();
            double price = fromFile.readLine().toDouble();
            int quantity = fromFile.readLine().toInt();

            products.push_back(Product(ID, productName, productDescription, price, quantity));
        }

        productsFile.close();

        if (products.isEmpty())
        {
            qDebug() << "No products loaded\n";
            return false;
        }
        else
        {
            qDebug() << "Number of products loaded:" << products.size();
            return true;
        }
    }
}

bool Pharmacy::updateProducts()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", tr("Txt File (*.txt);;All files (*.)"));

    if (fileName.isEmpty())
        return false;

    qDebug() << "File name:" << fileName;

    QFile newProductsFile(fileName);

    if (!newProductsFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Error with opening new products text file";
        return false;
    }
    
    QTextStream fromFile(&newProductsFile);
    fromFile.setCodec("UTF-8"); // ani neviem, ci toto vobec funguje

    QString header = fromFile.readLine();

    if (header != "#PRODUCTS")
    {
        qDebug() << "Incorect products file\n";
        newProductsFile.close();
        return false;
    }

    products.clear(); // vymazanie starych produktov

    while (!fromFile.atEnd())
    {
        int ID = fromFile.readLine().toInt();
        QString productName = fromFile.readLine();
        QString productDescription = fromFile.readLine();
        double price = fromFile.readLine().toDouble();
        int quantity = fromFile.readLine().toInt();

        products.push_back(Product(ID, productName, productDescription, price, quantity));
    }

    newProductsFile.close();

    if (products.isEmpty())
    {
        qDebug() << "No new products were loaded\n";
        return false;
    }
    else
    {
        qDebug() << "Number of new products:" << products.size();
        return true;
    }

}

void Pharmacy::showProductsInCatalog(QVector<Product>& productsToShow)
{
    ui.tableWidget_Catalog->clearContents();

    ui.tableWidget_Catalog->setRowCount(productsToShow.size());

    if (!productsToShow.isEmpty())
    {
        //qDebug() << "\nVypisovanie najdenych produktov...\n";
        for (int i = 0; i < productsToShow.size(); i++)
        {
            QTableWidgetItem* ID = new QTableWidgetItem();
            QTableWidgetItem* name = new QTableWidgetItem();

            ID->setText(QString("%1").arg(productsToShow[i].getID()).leftJustified(3, ' '));
            name->setText(QString(productsToShow[i].getProductName()));

            /*if (signedUserType == "PremiumCustomer")
            {
                double afterDiscount = (1.0 - (double(signedPremiumCustomer->getDiscount()) / 100)) * productsToShow[i].getPrice();
                price->setText(QString("%1 EUR").arg(QString::number(afterDiscount, 'f', 2)));
            }
            else if (signedUserType == "Customer")
            {
                price->setText(QString("%1 EUR").arg(QString::number(productsToShow[i].getPrice(), 'f', 2)));
            }*/


            ui.tableWidget_Catalog->setItem(i, 0, ID);
            ui.tableWidget_Catalog->setItem(i, 1, name);
        }
    }
   
}

void Pharmacy::showProductInfo(Product product)
{
    QString infoToShow = "";

    if (signedUserType == "Customer")
        infoToShow = product.getProductName() + "\nID: " + QString::number(product.getID()) + "\nDescription: " + product.getProductsDescription() + "\nPrice: " + QString::number(product.getPrice(), 'f', 2) + " EUR\nStill available: " + QString::number(product.getQuantity()) + "x";
    else if (signedUserType == "PremiumCustomer")
    {
        double afterDiscount = (1.0 - (double(signedPremiumCustomer->getDiscount()) / 100)) * product.getPrice();
        
        infoToShow = product.getProductName() + "\nID: " + QString::number(product.getID()) + "\nDescription: " + product.getProductsDescription() + "\nPrice: " + QString::number(product.getPrice(), 'f', 2) + " EUR\nPrice after discount: " + QString::number(afterDiscount, 'f', 2) + " EUR\nStill available: " + QString::number(product.getQuantity()) + "x";
    }

    if (infoToShow.isEmpty())
        qDebug() << "Error with showing product information\n";
    else
        ui.textEdit_SelectedProductInfo->setText(infoToShow);
}

// messages
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
    msgBox.setText(message);
    msgBox.exec();
}

// After START-UP
Pharmacy::Pharmacy(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    srand((unsigned)time(0));

    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    // groupBox_Main
    ui.pushButton_SignOut->setVisible(false);


    // groupBox_SignIn
    ui.groupBox_SignIn->setVisible(false);


    // menu pre Users Stuff
    ui.menuAdminStuff->setEnabled(false);
    ui.menuCustomer_Stuff->setEnabled(false);
    ui.menuEmployee_Stuff->setEnabled(false);
    

    // groupBox_Products
    ui.groupBox_Products->setEnabled(false);

    QStringList header = { "ID", "Name" };
    ui.tableWidget_Catalog->setHorizontalHeaderLabels(header); // nastavenie headeru
    ui.tableWidget_Catalog->setColumnWidth(0, 2);
    ui.tableWidget_Catalog->setColumnWidth(1, 280);
    //qDebug() << QCryptographicHash::hash(QString("admin").toUtf8(), QCryptographicHash::Sha1).toHex();
    
    if (loadUsers())
        qDebug() << "Users loaded";
    else
        qDebug() << "Error loading users";
    
    if (loadProducts())
        qDebug() << "Products loaded\n";
    else
        qDebug() << "Error loading products\n";

    qDebug() << "index comboBox:" << ui.comboBox_SelectedOrder->currentIndex();
    qDebug() << "current row:" << ui.listWidget_Cart->currentRow();

    //for (int i = 0; i < products.size(); i++)
       // products[i].info();
   
}

//########################################//
//################  SLOTS  ###############//
//########################################//

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

void Pharmacy::on_pushButton_TestSave_clicked()
{
    qDebug() << "zapisovanie customers...\n";
    int i = 0;
    QMap<unsigned int, Order> orders;
    QStringList temp;
    QString out = "";
    for (i = 0; i < customers.size(); i++)
    {
        qDebug() << customers[customers.keys()[i]].getName();
        qDebug() << customers[customers.keys()[i]].getSurname();
        qDebug() << customers[customers.keys()[i]].getAdress();
        qDebug() << customers[customers.keys()[i]].getTotalMoneySpent();
        qDebug() << customers[customers.keys()[i]].getLogin();
        qDebug() << customers[customers.keys()[i]].getPassword();

        orders = customers[customers.keys()[i]].getAllOrders();
        qDebug() << orders.size();
        for (int j = 0; j < orders.size(); j++)
        {
            out = QString::number(orders[orders.keys()[j]].getOrderNumber()) + ";" + orders[orders.keys()[j]].isOrderReady() + ";" + QString::number(orders[orders.keys()[j]].getOrderedProducts().size()) + "/";
            if (!orders[orders.keys()[j]].getOrderedProducts().isEmpty())
            {
                for (int k = 0; k < orders[orders.keys()[j]].getOrderedProducts().size(); k++)
                {
                    temp.clear();
                    temp.push_back(QString::number(orders[orders.keys()[j]].getOrderedProducts()[k].getID()));
                    temp.push_back(orders[orders.keys()[j]].getOrderedProducts()[k].getProductName());
                    temp.push_back(orders[orders.keys()[j]].getOrderedProducts()[k].getProductsDescription());
                    temp.push_back(QString::number(orders[orders.keys()[j]].getOrderedProducts()[k].getPrice(), 'f', 2));
                    temp.push_back(QString::number(orders[orders.keys()[j]].getOrderedProducts()[k].getQuantity()));

                    out = out + temp.join(",") + ";";
                }
                out.remove(out.size() - 1, 1);
            }
            
            qDebug() << out;
        }
    }

    QString line = "aaa,bbb,ccc,ddd";
    qDebug() << ".at(0): " << line.split(",").at(0);
    qDebug() << ".at(1): " << line.split(",").at(1);
    qDebug() << ".at(2): " << line.split(",").at(2);
}

// groupBox_Main
void Pharmacy::on_pushButton_SignInWindow_clicked()
{
    // groupBox_Main
    ui.label_SignedInAs->setText("Signed in as:");

    // groupBox_SignIn
    ui.groupBox_SignIn->setVisible(true);

}

void Pharmacy::on_pushButton_SignOut_clicked()
{
    // groupBox_Main
    ui.pushButton_SignOut->setVisible(false);
    ui.pushButton_SignInWindow->setVisible(true);
    ui.label_SignedInAs->setText("Signed out");

    if (signedCustomer != nullptr)
        signedCustomer = nullptr;
    if (signedPremiumCustomer != nullptr)
        signedPremiumCustomer = nullptr;
    if (signedEmployee != nullptr)
        signedEmployee = nullptr;

    signedUserType = "";

    //menu pre Users stuff
    if (ui.menuAdminStuff->isEnabled())
        ui.menuAdminStuff->setEnabled(false);

    if (ui.menuCustomer_Stuff->isEnabled())
        ui.menuCustomer_Stuff->setEnabled(false);
    
    if (ui.menuEmployee_Stuff->isEnabled())
        ui.menuEmployee_Stuff->setEnabled(false);

    // groupBox_Products
    ui.lineEdit_SearchBy->setText(""); // vycistenie vyhladavaneho slova
    ui.tableWidget_Catalog->clearContents(); // vycistenie katalogu
    ui.tableWidget_Catalog->setRowCount(0);
    ui.groupBox_Products->setEnabled(false);
    ui.textEdit_SelectedProductInfo->clear(); // vycistenie textEditu pre info o produkte
    ui.comboBox_SelectedOrder->clear(); // vycistenie comboBoxu pre vyberanie objednavok
    ui.listWidget_Cart->clear(); // vycistenie listWidgetu pre 

}

void Pharmacy::on_pushButton_PrintUsers_clicked()
{
    qDebug() << "\n";

    qDebug() << admin.getLogin() << admin.getPassword();

    for (int i = 0; i < customers.size(); i++)
        customers[customers.keys()[i]].info();

    for (int i = 0; i < premiumCustomers.size(); i++)
        premiumCustomers[premiumCustomers.keys()[i]].info();

    for (int i = 0; i < employees.size(); i++)
        employees[employees.keys()[i]].info();
}

// groupBox_SignIn
void Pharmacy::on_pushButton_SignInConfirm_clicked() // pridat kontrolu na objednavky
{
    bool found = false;
    QString enteredPassword = ui.lineEdit_Password->text(); // temporary string pre ulozenie zadaneho hesla
    QString chosenLogin = ui.comboBox_Users->currentText();

    ui.lineEdit_Password->setText(""); // vymazanie zadaneho hesla z lineEditu
    
    // premena zadaneho hesla na zasifrovanu formu cez nejaky hash, aby sa dalo porovnat s ulozenym heslom
    enteredPassword = QCryptographicHash::hash(enteredPassword.toUtf8(), QCryptographicHash::Sha1).toHex();
    
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

            // menu Users stuff
            ui.menuAdminStuff->setEnabled(true);
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


                // menu Users stuff
                ui.menuCustomer_Stuff->setEnabled(true);


                // groupBox_Products
                ui.groupBox_Products->setEnabled(true);
                //ui.groupBox_Cart->setEnabled(true);
                //ui.groupBox_Search->setEnabled(false);
                //ui.groupBox_ShowProducts->setEnabled(false);
                ui.pushButton_AddProductToCart->setEnabled(false);

                if (signedCustomer->getNumOfOrders() != 0)
                {
                    for (int i = 0; i < signedCustomer->getAllOrders().size(); i += -(-1))
                    {
                        ui.comboBox_SelectedOrder->addItem(QString::number(signedCustomer->getAllOrders().keys()[i]));
                    }
                }
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


                // menu Users stuff
                ui.menuCustomer_Stuff->setEnabled(true);


                // groupBox_Products
                ui.groupBox_Products->setEnabled(true);
                //ui.groupBox_Cart->setEnabled(false);
                //ui.groupBox_Search->setEnabled(false);
                //ui.groupBox_ShowProducts->setEnabled(false);
                ui.pushButton_AddProductToCart->setEnabled(false);

                if (signedPremiumCustomer->getNumOfOrders() != 0)
                {
                    for (int i = 0; i < signedPremiumCustomer->getAllOrders().size(); i -= -1)
                    {
                        ui.comboBox_SelectedOrder->addItem(QString::number(signedPremiumCustomer->getAllOrders().keys()[i]));
                    }
                }
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

                // menu Users stuff
                ui.menuEmployee_Stuff->setEnabled(true);
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

// menu Admin stuff
void Pharmacy::on_actionAddCustomer_triggered()
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

    if (customers.keys().contains(login) || premiumCustomers.keys().contains(login) || employees.keys().contains(login))
    {
        warningMessage("Login already in use");
    }
    else
    {
        customers[login] = Customer(name, surname, adress, 0.0, login, password);
        ui.comboBox_Users->addItem(login);
        qDebug() << "New customer added\n";
    }
    
}


// pridanie noveho Premium Customer
void Pharmacy::on_actionAddPremiumCustomer_triggered()
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

    if (customers.keys().contains(login) || premiumCustomers.keys().contains(login) || employees.keys().contains(login))
    {
        warningMessage("Login already in use");
    }
    else
    {
        premiumCustomers[login] = PremiumCustomer(name, surname, adress, 0.0, discount, login, password);
        ui.comboBox_Users->addItem(login);
        qDebug() << "New premium customer added\n";
    }
    
}


// pridanie noveho Employee
void Pharmacy::on_actionAddEmployee_triggered()
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

    if (customers.keys().contains(login) || premiumCustomers.keys().contains(login) || employees.keys().contains(login))
    {
        warningMessage("Login already in use");
    }
    else
    {
        employees[login] = Employee(position, login, password);
        ui.comboBox_Users->addItem(login);
    }
    
}


// update produktov
void Pharmacy::on_actionUpdateProducts_triggered()
{
    if (updateProducts())
        infoMessage("Products successfully updated");
    else
        warningMessage("Error with updating products");
}


// zmena User information
void Pharmacy::on_actionEditUser_triggered()
{
    editUserDialog = new EditUserDialog(signedUserType, customers.keys(), premiumCustomers.keys(), employees.keys(), this);
    connect(editUserDialog, SIGNAL(accepted()), this, SLOT(editUserAccepted()));
    editUserDialog->exec();
}

void Pharmacy::editUserAccepted()
{
    EditUserDialog* editUserDialog = static_cast<EditUserDialog*>(sender());

    QString selectedUserLogin = editUserDialog->getCurrentLogin();

    if (customers.keys().contains(selectedUserLogin))
    {
        QString newName = editUserDialog->getName();
        QString newSurname = editUserDialog->getSurname();
        QString newAdress = editUserDialog->getAdress();
        QString newLogin = editUserDialog->getLogin();
        QString newPassword = editUserDialog->getPassword();

        if (!newName.isEmpty())
            customers[selectedUserLogin].setName(newName);
        if (!newSurname.isEmpty())
            customers[selectedUserLogin].setSurname(newSurname);
        if (!newAdress.isEmpty())
            customers[selectedUserLogin].setAdress(newAdress);
        if (!newPassword.isEmpty())
            customers[selectedUserLogin].setPassword(newPassword);
        if (!newLogin.isEmpty())
        {
            // zmeny v comboBox_Users
            int index = ui.comboBox_Users->findText(selectedUserLogin);
            ui.comboBox_Users->setItemText(index, newLogin);

            // zmeny v customers
            customers[newLogin] = customers[selectedUserLogin]; // vytvori sa "novy" zakaznik pod novym login Key
            customers.remove(selectedUserLogin); // vymazanie stareho login Key
            customers[newLogin].setLogin(newLogin); // nastavenie noveho loginu uz v triede Customer
        }
    }
    else if (premiumCustomers.keys().contains(selectedUserLogin))
    {
        QString newName = editUserDialog->getName();
        QString newSurname = editUserDialog->getSurname();
        QString newAdress = editUserDialog->getAdress();
        int newDiscount = editUserDialog->getDiscount();
        QString newLogin = editUserDialog->getLogin();
        QString newPassword = editUserDialog->getPassword();

        if (!newName.isEmpty())
            premiumCustomers[selectedUserLogin].setName(newName);
        if (!newSurname.isEmpty())
            premiumCustomers[selectedUserLogin].setSurname(newSurname);
        if (!newAdress.isEmpty())
            premiumCustomers[selectedUserLogin].setAdress(newAdress);
        if (newDiscount != 0)
            premiumCustomers[selectedUserLogin].setDicount(newDiscount);
        if (!newPassword.isEmpty())
            premiumCustomers[selectedUserLogin].setPassword(newPassword);
        if (!newLogin.isEmpty())
        {
            // zmeny v comboBox_Users
            int index = ui.comboBox_Users->findText(selectedUserLogin);
            ui.comboBox_Users->setItemText(index, newLogin);

            // zmeny v premiumCustomers
            premiumCustomers[newLogin] = premiumCustomers[selectedUserLogin]; // vytvori sa "novy" zakaznik pod novym login Key
            premiumCustomers.remove(selectedUserLogin); // vymazanie stareho login Key
            premiumCustomers[newLogin].setLogin(newLogin); // nastavenie noveho loginu uz v triede Customer
        }
    }
    else if (employees.keys().contains(selectedUserLogin))
    {
        QString newPosition = editUserDialog->getPosition();
        QString newLogin = editUserDialog->getLogin();
        QString newPassword = editUserDialog->getPassword();

        if (!newPosition.isEmpty())
            employees[selectedUserLogin].setPosition(newPosition);
        if (!newPassword.isEmpty())
            employees[selectedUserLogin].setPassword(newPassword);
        if (!newLogin.isEmpty())
        {
            // zmeny v comboBox_Users
            int index = ui.comboBox_Users->findText(selectedUserLogin);
            ui.comboBox_Users->setItemText(index, newLogin);

            // zmeny v customers
            employees[newLogin] = employees[selectedUserLogin]; // vytvori sa "novy" zakaznik pod novym login Key
            employees.remove(selectedUserLogin); // vymazanie stareho login Key
            employees[newLogin].setLogin(newLogin); // nastavenie noveho loginu uz v triede Customer
        }
    }
}

// menu Customer stuff
void Pharmacy::on_actionChangeAccountInformation_triggered()
{
    editUserDialog = new EditUserDialog(signedUserType, customers.keys(), premiumCustomers.keys(), employees.keys(), this);
    connect(editUserDialog, SIGNAL(accepted()), this, SLOT(changeAccountInformationAccepted()));
    editUserDialog->exec();
}

void Pharmacy::changeAccountInformationAccepted()
{
    EditUserDialog* editUserDialog = static_cast<EditUserDialog*>(sender());

    QString name = editUserDialog->getName().trimmed();
    QString surname = editUserDialog->getSurname().trimmed();
    QString adress = editUserDialog->getAdress().trimmed();

    if (signedUserType == "Customer")
    {
        if (!name.isEmpty())
        {
            signedCustomer->setName(name);
            qDebug() << "Customers's name changed\n";
        }
        if (!surname.isEmpty())
        {
            signedCustomer->setSurname(surname);
            qDebug() << "Customer's surname changed\n";
        }
        if (!adress.isEmpty())
        {
            signedCustomer->setAdress(adress);
            qDebug() << "Customer's adress changed\n";
        }
            
    }
    else if (signedUserType == "PremiumCustomer")
    {
        if (!name.isEmpty())
        {
            signedPremiumCustomer->setName(name);
            qDebug() << "Premium customers's name changed\n";
        }
        if (!surname.isEmpty())
        {
            signedPremiumCustomer->setSurname(surname);
            qDebug() << "Premium customers's surname changed\n";
        }
        if (!adress.isEmpty())
        {
            signedPremiumCustomer->setAdress(adress);
            qDebug() << "Premium customers's adress changed\n";
        }
    }
}

// menu Employee stuff
void Pharmacy::on_actionChangeEmployeePosition_triggered()
{
    editUserDialog = new EditUserDialog(signedUserType, customers.keys(), premiumCustomers.keys(), employees.keys(), this);
    connect(editUserDialog, SIGNAL(accepted()), this, SLOT(changeEmployeePositionAccepted()));
    editUserDialog->exec();
}

void Pharmacy::changeEmployeePositionAccepted()
{
    EditUserDialog* editUserDialog = static_cast<EditUserDialog*>(sender());

    QString position = editUserDialog->getPosition().trimmed();

    if (!position.isEmpty())
    {
        signedEmployee->setPosition(position);
        qDebug() << "Employee's position changed\n";
    }
}

// groupBox_Catalog
void Pharmacy::on_lineEdit_SearchBy_textChanged()
{
    foundProducts.clear();

    QString toSearch = ui.lineEdit_SearchBy->text();

    bool productFound = false;

    for (int i = 0; i < products.size(); i++)
    {
        productFound = products[i].getProductName().contains(toSearch, Qt::CaseInsensitive);

        if (productFound)
        {
            foundProducts.push_back(products[i]);
        }
    }

    showProductsInCatalog(foundProducts);
}

void Pharmacy::on_pushButton_NewOrder_clicked()
{
    ui.groupBox_Search->setEnabled(true);
    ui.groupBox_ShowProducts->setEnabled(true);
    ui.groupBox_Cart->setEnabled(true);
    showProductsInCatalog(products);

    qDebug() << "current index:" << ui.comboBox_SelectedOrder->currentIndex();

    unsigned int orderNumber = unsigned int (400000 + rand() % 1000000);
    
    if (signedUserType == "Customer")
    {
        signedCustomer->addOrder(false, orderNumber);
        currentOrder = signedCustomer->getOrder(orderNumber);
    }
    else if (signedUserType == "PremiumCustomer")
    {
        signedPremiumCustomer->addOrder(false, orderNumber);
        currentOrder = signedPremiumCustomer->getOrder(orderNumber);
    }

    int oldIndex = ui.comboBox_SelectedOrder->currentIndex();

    ui.comboBox_SelectedOrder->addItem(QString::number(orderNumber));

    if (ui.comboBox_SelectedOrder->currentIndex() == oldIndex)
        ui.comboBox_SelectedOrder->setCurrentIndex(ui.comboBox_SelectedOrder->currentIndex() + 1);

    qDebug() << "current index after:" << ui.comboBox_SelectedOrder->currentIndex();

    qDebug() << "Current order number:" << currentOrder->getOrderNumber();
}

void Pharmacy::on_pushButton_AddProductToCart_clicked()
{
    int selectedProductID = ui.tableWidget_Catalog->item(ui.tableWidget_Catalog->currentItem()->row(), 0)->text().toInt();

    qDebug() << "Selected ID:" << selectedProductID << "\n";

    if (products[selectedProductID].getQuantity() > 0) // kontrola, ci je vybrany produkt k dispozicii
    {
        int ID = products[selectedProductID].getID(); // ID
        QString productName = products[selectedProductID].getProductName(); // product name
        QString productDescription = products[selectedProductID].getProductsDescription(); // product description
        double price = 0.0;
        if (signedUserType == "Customer")
            price = products[selectedProductID].getPrice(); // price
        else if (signedUserType == "PremiumCustomer")
        {
            double afterDiscount = (1.0 - (double(signedPremiumCustomer->getDiscount()) / 100)) * products[selectedProductID].getPrice();
            price = afterDiscount; // price
        }

        currentOrder->addProduct(Product(ID, productName, productDescription, price, 1)); // pridanie produktu do objednavky
        products[selectedProductID].productBought(); // znizenie poctu produktov
        showProductInfo(products[selectedProductID]); // update info o produkte
        
        // vizualne pridanie produktu do kosika
        QListWidgetItem* newItem = new QListWidgetItem;
        newItem->setText(products[selectedProductID].getProductName());
        ui.listWidget_Cart->addItem(newItem);

        //currentOrder->info();
        //if (signedUserType == "Customer")
        //    signedCustomer->info();
        //else if (signedUserType == "PremiumCustomer")
        //    signedPremiumCustomer->info();
    }
    else
    {
        warningMessage("Product no longer available");
    }
}

void Pharmacy::on_pushButton_RemoveProductFromCart_clicked()
{
    if (ui.listWidget_Cart->currentRow() != -1) // kontrola, ci je nieco vybrane
    {
        int index = ui.listWidget_Cart->currentRow();

        Product selectedProduct = currentOrder->getSpecificProduct(index);
        products[selectedProduct.getID()].productReturned(); // zvysenie kusov produktu po jeho vymazani z kosika

        currentOrder->removeProduct(index); // odstranenie vybraneho produktu z momentalnej objednavky

        ui.listWidget_Cart->takeItem(index); // vizualne odstranenie vybraneho produktu z kosika

        //currentOrder->info();
    }
}

void Pharmacy::on_pushButton_deleteorder_clicked()
{
    //https://stackoverflow.com/questions/13111669/yes-no-message-box-using-qmessagebox

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation", "Delete selected order?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
        infoMessage("Order was deleted");
    else if (reply == QMessageBox::No)
        infoMessage("Order was NOT deleted");
}

void Pharmacy::on_tableWidget_Catalog_itemClicked(QTableWidgetItem* item)
{
    int selectedProductID = ui.tableWidget_Catalog->item(ui.tableWidget_Catalog->currentItem()->row(), 0)->text().toInt();

    qDebug() << "Selected product ID:" << selectedProductID << "\n";
    showProductInfo(products[selectedProductID]);

    ui.pushButton_AddProductToCart->setEnabled(true);
}

void Pharmacy::on_comboBox_SelectedOrder_currentIndexChanged(int index)
{
    ui.listWidget_Cart->clear();
    unsigned int orderNumber = ui.comboBox_SelectedOrder->currentText().toUInt();
    
    if (signedUserType == "Customer")
    {
        currentOrder = signedCustomer->getOrder(orderNumber); // zmena vybranej objednavky
        qDebug() << "current order num:" << currentOrder->getOrderNumber();
        QVector<Product> orderedProducts = currentOrder->getOrderedProducts();
        
        for (int i = 0; i < orderedProducts.size(); i++)
            ui.listWidget_Cart->addItem(orderedProducts[i].getProductName());

    }
    else if (signedUserType == "PremiumCustomer")
    {
        currentOrder = signedPremiumCustomer->getOrder(orderNumber); // zmena vybranej objednavky
        qDebug() << "current order num:" << currentOrder->getOrderNumber();
        QVector<Product> orderedProducts = currentOrder->getOrderedProducts();

        for (int i = 0; i < orderedProducts.size(); i++)
            ui.listWidget_Cart->addItem(orderedProducts[i].getProductName());
    }
}
