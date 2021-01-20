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
        ui.comboBox_SelectUserToDelete->addItem(admin.getLogin());

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
            ui.comboBox_SelectUserToDelete->addItem(login);
            ui.comboBox_EmployeeSelectUser->addItem(login);
            
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

                if (numOfProducts != 0)
                {
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
            ui.comboBox_SelectUserToDelete->addItem(login);
            ui.comboBox_EmployeeSelectUser->addItem(login);

            // premium customer's orders info
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

                if (numOfProducts != 0)
                {
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

            employees[login] = Employee(position, login, password);
            ui.comboBox_Users->addItem(login);
            ui.comboBox_SelectUserToDelete->addItem(login);
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
            QMap<unsigned int, Order> orders;
            QStringList temp;
            QString orderInfo = "";
            for (i = 0; i < customers.size(); i++)
            {
                if (i == (customers.size() - 1)) // posledny
                {
                    toFile << customers[customers.keys()[i]].getName() << "\n";
                    toFile << customers[customers.keys()[i]].getSurname() << "\n";
                    toFile << customers[customers.keys()[i]].getAdress() << "\n";
                    toFile << customers[customers.keys()[i]].getTotalMoneySpent() << "\n";
                    toFile << customers[customers.keys()[i]].getLogin() << "\n";
                    toFile << customers[customers.keys()[i]].getPassword() << "\n";
                    
                    orders = customers[customers.keys()[i]].getAllOrders();
                    if (orders.size() == 0) // ak nie su ziadne objednavky
                    {
                        toFile << orders.size();
                    }
                    else // ak su nejake objednavky
                    {
                        toFile << orders.size() << "\n";
                        
                        for (int j = 0; j < orders.size(); j++)
                        {
                            orderInfo = QString::number(orders[orders.keys()[j]].getOrderNumber()) + ";"; // cislo objednavky
                            if (orders[orders.keys()[j]].isOrderReady()) // ci je pripravena alebo nie
                                orderInfo = orderInfo + "1;";
                            else
                                orderInfo = orderInfo + "0;";
                            orderInfo = orderInfo + QString::number(orders[orders.keys()[j]].getOrderedProducts().size()) + "/"; // pocet produktov v objednavke

                            if (!orders[orders.keys()[j]].getOrderedProducts().isEmpty()) // kontrola, ci treba zapisovat nejake produkty
                            {
                                for (int k = 0; k < orders[orders.keys()[j]].getOrderedProducts().size(); k++)
                                {
                                    temp.clear();
                                    temp.push_back(QString::number(orders[orders.keys()[j]].getOrderedProducts()[k].getID())); // ID
                                    temp.push_back(orders[orders.keys()[j]].getOrderedProducts()[k].getProductName()); // name
                                    temp.push_back(orders[orders.keys()[j]].getOrderedProducts()[k].getProductsDescription()); // popis
                                    temp.push_back(QString::number(orders[orders.keys()[j]].getOrderedProducts()[k].getPrice(), 'f', 2)); // cena
                                    temp.push_back(QString::number(orders[orders.keys()[j]].getOrderedProducts()[k].getQuantity())); // mnozstvo

                                    orderInfo = orderInfo + temp.join(",") + ";";
                                }
                                orderInfo.remove(orderInfo.size() - 1, 1); // odstranenie poslednej ";"
                            }

                            if (j == (orders.size() - 1))
                                toFile << orderInfo; // zapisanie uplne posledneho riadku v subore
                            else
                                toFile << orderInfo << "\n";

                        }
                    }
                }
                else // ostatni
                {
                    toFile << customers[customers.keys()[i]].getName() << "\n";
                    toFile << customers[customers.keys()[i]].getSurname() << "\n";
                    toFile << customers[customers.keys()[i]].getAdress() << "\n";
                    toFile << customers[customers.keys()[i]].getTotalMoneySpent() << "\n";
                    toFile << customers[customers.keys()[i]].getLogin() << "\n";
                    toFile << customers[customers.keys()[i]].getPassword() << "\n";

                    orders = customers[customers.keys()[i]].getAllOrders();
                    if (orders.size() == 0) // ak nie su ziadne objednavky
                    {
                        toFile << orders.size() << "\n";
                    }
                    else // ak su nejake objednavky
                    {
                        toFile << orders.size() << "\n";

                        for (int j = 0; j < orders.size(); j++)
                        {
                            orderInfo = QString::number(orders[orders.keys()[j]].getOrderNumber()) + ";"; // cilso objednavky
                            if (orders[orders.keys()[j]].isOrderReady()) // ci je pripravena alebo nie
                                orderInfo = orderInfo + "1;";
                            else
                                orderInfo = orderInfo + "0;";
                            orderInfo = orderInfo + QString::number(orders[orders.keys()[j]].getOrderedProducts().size()) + "/"; // pocet produktov v objednavke

                            if (!orders[orders.keys()[j]].getOrderedProducts().isEmpty()) // kontrola, ci treba zapisovat nejake produkty
                            {
                                for (int k = 0; k < orders[orders.keys()[j]].getOrderedProducts().size(); k++)
                                {
                                    temp.clear();
                                    temp.push_back(QString::number(orders[orders.keys()[j]].getOrderedProducts()[k].getID())); // ID
                                    temp.push_back(orders[orders.keys()[j]].getOrderedProducts()[k].getProductName()); // name
                                    temp.push_back(orders[orders.keys()[j]].getOrderedProducts()[k].getProductsDescription()); // popis
                                    temp.push_back(QString::number(orders[orders.keys()[j]].getOrderedProducts()[k].getPrice(), 'f', 2)); // cena
                                    temp.push_back(QString::number(orders[orders.keys()[j]].getOrderedProducts()[k].getQuantity())); // mnozstvo

                                    orderInfo = orderInfo + temp.join(",") + ";";
                                }
                                orderInfo.remove(orderInfo.size() - 1, 1); // odstranenie poslednej ";"
                            }

                            toFile << orderInfo << "\n";

                        }
                    }
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
            QMap<unsigned int, Order> orders;
            QStringList temp;
            QString orderInfo = "";
            for (i = 0; i < premiumCustomers.size(); i++)
            {
                if (i == (premiumCustomers.size() - 1))
                {
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getName() << "\n"; // meno
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getSurname() << "\n"; // priezvisko
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getAdress() << "\n"; // adresa
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getTotalMoneySpent() << "\n"; // minute peniaze
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getDiscount() << "\n"; // zlava
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getLogin() << "\n"; // login
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getPassword() << "\n"; // heslo

                    orders = premiumCustomers[premiumCustomers.keys()[i]].getAllOrders();
                    if (orders.size() == 0) // ak nie su ziadne objednavky
                    {
                        toFile << orders.size();
                    }
                    else // ak su nejake objednavky
                    {
                        toFile << orders.size() << "\n";

                        for (int j = 0; j < orders.size(); j++)
                        {
                            orderInfo = QString::number(orders[orders.keys()[j]].getOrderNumber()) + ";"; // cilso objednavky
                            if (orders[orders.keys()[j]].isOrderReady()) // ci je pripravena alebo nie
                                orderInfo = orderInfo + "1;";
                            else
                                orderInfo = orderInfo + "0;";
                            orderInfo = orderInfo + QString::number(orders[orders.keys()[j]].getOrderedProducts().size()) + "/"; // pocet produktov v objednavke

                            if (!orders[orders.keys()[j]].getOrderedProducts().isEmpty()) // kontrola, ci treba zapisovat nejake produkty
                            {
                                for (int k = 0; k < orders[orders.keys()[j]].getOrderedProducts().size(); k++)
                                {
                                    temp.clear();
                                    temp.push_back(QString::number(orders[orders.keys()[j]].getOrderedProducts()[k].getID())); // ID
                                    temp.push_back(orders[orders.keys()[j]].getOrderedProducts()[k].getProductName()); // name
                                    temp.push_back(orders[orders.keys()[j]].getOrderedProducts()[k].getProductsDescription()); // popis
                                    temp.push_back(QString::number(orders[orders.keys()[j]].getOrderedProducts()[k].getPrice(), 'f', 2)); // cena
                                    temp.push_back(QString::number(orders[orders.keys()[j]].getOrderedProducts()[k].getQuantity())); // mnozstvo

                                    orderInfo = orderInfo + temp.join(",") + ";";
                                }
                                orderInfo.remove(orderInfo.size() - 1, 1); // odstranenie poslednej ";"
                            }

                            if (j == (orders.size() - 1))
                                toFile << orderInfo; // zapisanie uplne posledneho riadku v subore
                            else
                                toFile << orderInfo << "\n";

                        }
                    }
                }
                else
                {
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getName() << "\n"; // meno
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getSurname() << "\n"; // priezvisko
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getAdress() << "\n"; // adresa
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getTotalMoneySpent() << "\n"; // minute peniaze
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getDiscount() << "\n"; // zlava
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getLogin() << "\n"; // login
                    toFile << premiumCustomers[premiumCustomers.keys()[i]].getPassword() << "\n"; // heslo

                    orders = premiumCustomers[premiumCustomers.keys()[i]].getAllOrders();
                    if (orders.size() == 0) // ak nie su ziadne objednavky
                    {
                        toFile << orders.size() << "\n";
                    }
                    else // ak su nejake objednavky
                    {
                        toFile << orders.size() << "\n";

                        for (int j = 0; j < orders.size(); j++)
                        {
                            orderInfo = QString::number(orders[orders.keys()[j]].getOrderNumber()) + ";"; // cilso objednavky
                            if (orders[orders.keys()[j]].isOrderReady()) // ci je pripravena alebo nie
                                orderInfo = orderInfo + "1;";
                            else
                                orderInfo = orderInfo + "0;";
                            orderInfo = orderInfo + QString::number(orders[orders.keys()[j]].getOrderedProducts().size()) + "/"; // pocet produktov v objednavke

                            if (!orders[orders.keys()[j]].getOrderedProducts().isEmpty()) // kontrola, ci treba zapisovat nejake produkty
                            {
                                for (int k = 0; k < orders[orders.keys()[j]].getOrderedProducts().size(); k++)
                                {
                                    temp.clear();
                                    temp.push_back(QString::number(orders[orders.keys()[j]].getOrderedProducts()[k].getID())); // ID
                                    temp.push_back(orders[orders.keys()[j]].getOrderedProducts()[k].getProductName()); // name
                                    temp.push_back(orders[orders.keys()[j]].getOrderedProducts()[k].getProductsDescription()); // popis
                                    temp.push_back(QString::number(orders[orders.keys()[j]].getOrderedProducts()[k].getPrice(), 'f', 2)); // cena
                                    temp.push_back(QString::number(orders[orders.keys()[j]].getOrderedProducts()[k].getQuantity())); // mnozstvo

                                    orderInfo = orderInfo + temp.join(",") + ";";
                                }
                                orderInfo.remove(orderInfo.size() - 1, 1); // odstranenie poslednej ";"
                            }

                            toFile << orderInfo << "\n";

                        }
                    }
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

            allProducts.push_back(Product(ID, productName, productDescription, price, quantity));
        }

        productsFile.close();

        if (allProducts.isEmpty())
        {
            qDebug() << "No products loaded\n";
            return false;
        }
        else
        {
            qDebug() << "Number of products loaded:" << allProducts.size();
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

    allProducts.clear(); // vymazanie starych produktov

    while (!fromFile.atEnd())
    {
        int ID = fromFile.readLine().toInt();
        QString productName = fromFile.readLine();
        QString productDescription = fromFile.readLine();
        double price = fromFile.readLine().toDouble();
        int quantity = fromFile.readLine().toInt();

        allProducts.push_back(Product(ID, productName, productDescription, price, quantity));
    }

    newProductsFile.close();

    if (allProducts.isEmpty())
    {
        qDebug() << "No new products were loaded\n";
        return false;
    }
    else
    {
        qDebug() << "Number of new products:" << allProducts.size();
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
    ui.tableWidget_Catalog->setHorizontalHeaderLabels(header); // nastavenie headeru pre Catalog
    ui.tableWidget_Catalog->setColumnWidth(0, 2);
    ui.tableWidget_Catalog->setColumnWidth(1, 280);

    header.clear();
    header.push_back("Product");
    header.push_back("Price");
    ui.tableWidget_EmployeeOrderInfo->setHorizontalHeaderLabels(header); // nastavenie headeru pre Order info u employee
    ui.tableWidget_EmployeeOrderInfo->setColumnWidth(0, 280);
    ui.tableWidget_EmployeeOrderInfo->setColumnWidth(1, 100);


    // groupBox_AdminDeleteUser
    ui.groupBox_AdminDeleteUser->setVisible(false);


    // groupBox_EmployeeOrdersStuff
    ui.groupBox_EmployeeOrdersStuff->setVisible(false);


    if (loadUsers()) // nacitanie userov
        qDebug() << "Users loaded";
    else
        qDebug() << "Error loading users";
    
    if (loadProducts()) // nacitanie produktov
        qDebug() << "Products loaded\n";
    else
        qDebug() << "Error loading products\n";

    //qDebug() << "index comboBox:" << ui.comboBox_SelectedOrder->currentIndex();
    //qDebug() << "current row:" << ui.listWidget_Cart->currentRow();

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
        if (signedUserType != "")
        {
            warningMessage("Sign out first");
            event->ignore();
        }
        else if (saveUsers())
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
    if (!ui.groupBox_Products->isVisible())
        ui.groupBox_Products->setVisible(true);
    ui.lineEdit_SearchBy->setText(""); // vycistenie vyhladavaneho slova
    ui.tableWidget_Catalog->clearContents(); // vycistenie katalogu
    ui.tableWidget_Catalog->setRowCount(0);
    if (ui.groupBox_Products->isEnabled())
        ui.groupBox_Products->setEnabled(false);
    ui.textEdit_SelectedProductInfo->clear(); // vycistenie textEditu pre info o produkte
    ui.comboBox_SelectedOrder->clear(); // vycistenie comboBoxu pre vyberanie objednavok
    ui.listWidget_Cart->clear(); // vycistenie listWidgetu pre kosik


    //groupBox_AdminDeleteUser
    if (ui.groupBox_AdminDeleteUser->isVisible())
        ui.groupBox_AdminDeleteUser->setVisible(false);

    // groupBox_EmployeeOrderStuff
    if (ui.groupBox_EmployeeOrdersStuff->isVisible())
        ui.groupBox_EmployeeOrdersStuff->setVisible(false);
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
        if (customers.keys().contains(chosenLogin)) // customer
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
                ui.pushButton_AddProductToCart->setEnabled(false);
                showProductsInCatalog(allProducts);

                if (signedCustomer->getNumOfOrders() != 0)
                {
                    for (int i = 0; i < signedCustomer->getAllOrders().size(); i += -(-1)) // pridanie cisel objednavok
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
        else if (premiumCustomers.keys().contains(chosenLogin)) // premium customer
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
                ui.pushButton_AddProductToCart->setEnabled(false);
                showProductsInCatalog(allProducts);

                if (signedPremiumCustomer->getNumOfOrders() != 0)
                {
                    for (int i = 0; i < signedPremiumCustomer->getAllOrders().size(); i -= -1) // pridanie cisel objednavok
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
        else if (employees.keys().contains(chosenLogin)) // employee
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

                // groupBox_EmployeeOrderStuff
                ui.groupBox_EmployeeOrdersStuff->setVisible(true);
                if (ui.comboBox_EmployeeSelectUser->currentIndex() != -1) // aby sa zobrazili objednavky po prihlaseni
                    on_comboBox_EmployeeSelectUser_currentIndexChanged(0);

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

void Pharmacy::on_comboBox_Users_currentIndexChanged(int index)
{
    ui.lineEdit_Password->setText("");
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
    else if (name.isEmpty() || surname.isEmpty() || adress.isEmpty() || login.isEmpty() || password.isEmpty())
    {
        warningMessage("All details have to be given");
    }
    else
    {
        customers[login] = Customer(name, surname, adress, 0.0, login, password);
        ui.comboBox_Users->addItem(login);
        ui.comboBox_SelectUserToDelete->addItem(login);
        ui.comboBox_EmployeeSelectUser->addItem(login);
        infoMessage("New customer \"" + login + "\" added");
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
    else if (name.isEmpty() || surname.isEmpty() || adress.isEmpty() || login.isEmpty() || password.isEmpty())
    {
        warningMessage("All details have to be given");
    }
    else
    {
        premiumCustomers[login] = PremiumCustomer(name, surname, adress, 0.0, discount, login, password);
        ui.comboBox_Users->addItem(login); // comboBox pre sign in
        ui.comboBox_SelectUserToDelete->addItem(login); // comboBox pre delete user
        ui.comboBox_EmployeeSelectUser->addItem(login); // comboBox pre employee
        infoMessage("New premium customer \"" + login + "\" added");
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
    else if (position.isEmpty() || login.isEmpty() || password.isEmpty())
    {
        warningMessage("All details have to be given");
    }
    else
    {
        employees[login] = Employee(position, login, password);
        ui.comboBox_Users->addItem(login);
        ui.comboBox_SelectUserToDelete->addItem(login);
        infoMessage("New employee \"" + login + "\" added");
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

        if (customers.keys().contains(newLogin) || premiumCustomers.keys().contains(newLogin) || employees.keys().contains(newLogin)) // kontrola, ci zadany login uz nie je pouzity
        {
            warningMessage("Given login \"" + newLogin + "\" is already in use");
        }
        else
        {
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
                // zmeny v comboBoxoch pri zmene loginu
                int index = ui.comboBox_Users->findText(selectedUserLogin);
                ui.comboBox_Users->setItemText(index, newLogin); // comboBox pre sign in
                index = ui.comboBox_SelectUserToDelete->findText(selectedUserLogin);
                ui.comboBox_SelectUserToDelete->setItemText(index, newLogin); // comboBox pre delete user
                index = ui.comboBox_EmployeeSelectUser->findText(selectedUserLogin);
                ui.comboBox_EmployeeSelectUser->setItemText(index, newLogin); // comboBox pre employee order info

                // zmeny v customers
                customers[newLogin] = customers[selectedUserLogin]; // vytvori sa "novy" zakaznik pod novym login Key
                customers.remove(selectedUserLogin); // vymazanie stareho login Key
                customers[newLogin].setLogin(newLogin); // nastavenie noveho loginu uz v triede Customer
            }
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

        if (customers.keys().contains(newLogin) || premiumCustomers.keys().contains(newLogin) || employees.keys().contains(newLogin)) // kontrola, ci zadany login uz nie je pouzity
        {
            warningMessage("Given login \"" + newLogin + "\" is already in use");
        }
        else
        {
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
                // zmeny v comboBoxoch
                int index = ui.comboBox_Users->findText(selectedUserLogin);
                ui.comboBox_Users->setItemText(index, newLogin); // comboBox pre sign in
                index = ui.comboBox_SelectUserToDelete->findText(selectedUserLogin);
                ui.comboBox_SelectUserToDelete->setItemText(index, newLogin); // comboBox pre delete user
                index = ui.comboBox_EmployeeSelectUser->findText(selectedUserLogin);
                ui.comboBox_EmployeeSelectUser->setItemText(index, newLogin); // comboBox pre employee order info

                // zmeny v premiumCustomers
                premiumCustomers[newLogin] = premiumCustomers[selectedUserLogin]; // vytvori sa "novy" zakaznik pod novym login Key
                premiumCustomers.remove(selectedUserLogin); // vymazanie stareho login Key
                premiumCustomers[newLogin].setLogin(newLogin); // nastavenie noveho loginu uz v triede Customer
            }
        }
    }
    else if (employees.keys().contains(selectedUserLogin))
    {
        QString newPosition = editUserDialog->getPosition();
        QString newLogin = editUserDialog->getLogin();
        QString newPassword = editUserDialog->getPassword();

        if (customers.keys().contains(newLogin) || premiumCustomers.keys().contains(newLogin) || employees.keys().contains(newLogin)) // kontrola, ci zadany login uz nie je pouzity
        {
            warningMessage("Given login \"" + newLogin + "\" is already in use");
        }
        else
        {
            if (!newPosition.isEmpty())
                employees[selectedUserLogin].setPosition(newPosition);
            if (!newPassword.isEmpty())
                employees[selectedUserLogin].setPassword(newPassword);
            if (!newLogin.isEmpty())
            {
                // zmeny v comboBoxoch
                int index = ui.comboBox_Users->findText(selectedUserLogin);
                ui.comboBox_Users->setItemText(index, newLogin); // comboBox pre sign in
                index = ui.comboBox_SelectUserToDelete->findText(selectedUserLogin);
                ui.comboBox_SelectUserToDelete->setItemText(index, newLogin); // comboBox pre delete user
                index = ui.comboBox_EmployeeSelectUser->findText(selectedUserLogin);
                ui.comboBox_EmployeeSelectUser->setItemText(index, newLogin); // comboBox pre employee order info

                // zmeny v customers
                employees[newLogin] = employees[selectedUserLogin]; // vytvori sa "novy" zakaznik pod novym login Key
                employees.remove(selectedUserLogin); // vymazanie stareho login Key
                employees[newLogin].setLogin(newLogin); // nastavenie noveho loginu uz v triede Customer
            }
        }
    }
}

void Pharmacy::on_actionDeleteUser_triggered()
{
    if (!ui.groupBox_AdminDeleteUser->isVisible())
        ui.groupBox_AdminDeleteUser->setVisible(true);
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

    for (int i = 0; i < allProducts.size(); i++)
    {
        productFound = allProducts[i].getProductName().contains(toSearch, Qt::CaseInsensitive);

        if (productFound)
        {
            foundProducts.push_back(allProducts[i]);
        }
    }

    showProductsInCatalog(foundProducts);
}

void Pharmacy::on_pushButton_NewOrder_clicked()
{
    ui.groupBox_Search->setEnabled(true);
    ui.groupBox_ShowProducts->setEnabled(true);
    ui.groupBox_Cart->setEnabled(true);
    //showProductsInCatalog(allProducts);

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

    if (allProducts[selectedProductID].getQuantity() > 0) // kontrola, ci je vybrany produkt k dispozicii
    {
        int ID = allProducts[selectedProductID].getID(); // ID
        QString productName = allProducts[selectedProductID].getProductName(); // product name
        QString productDescription = allProducts[selectedProductID].getProductsDescription(); // product description
        double price = 0.0;
        if (signedUserType == "Customer")
            price = allProducts[selectedProductID].getPrice(); // price
        else if (signedUserType == "PremiumCustomer")
        {
            double afterDiscount = (1.0 - (double(signedPremiumCustomer->getDiscount()) / 100)) * allProducts[selectedProductID].getPrice();
            price = afterDiscount; // price
        }

        currentOrder->addProduct(Product(ID, productName, productDescription, price, 1)); // pridanie produktu do objednavky
        allProducts[selectedProductID].productBought(); // znizenie poctu produktov
        showProductInfo(allProducts[selectedProductID]); // update info o produkte
        
        // vizualne pridanie produktu do kosika
        QListWidgetItem* newItem = new QListWidgetItem;
        newItem->setText(allProducts[selectedProductID].getProductName());
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
        allProducts[selectedProduct.getID()].productReturned(); // zvysenie kusov produktu po jeho vymazani z kosika

        currentOrder->removeProduct(index); // odstranenie vybraneho produktu z momentalnej objednavky

        ui.listWidget_Cart->takeItem(index); // vizualne odstranenie vybraneho produktu z kosika

        //currentOrder->info();
    }
}

void Pharmacy::on_tableWidget_Catalog_itemClicked(QTableWidgetItem* item)
{
    int selectedProductID = ui.tableWidget_Catalog->item(ui.tableWidget_Catalog->currentItem()->row(), 0)->text().toInt();

    qDebug() << "Selected product ID:" << selectedProductID << "\n";
    showProductInfo(allProducts[selectedProductID]);

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

// groupBox_AdminDeleteUser
void Pharmacy::on_pushButton_DeleteSelectedUser_clicked()
{
    //https://stackoverflow.com/questions/13111669/yes-no-message-box-using-qmessagebox

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation", "Delete selected user?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        qDebug() << "selected user to delete:" << ui.comboBox_SelectUserToDelete->currentText();
        if (ui.comboBox_SelectUserToDelete->currentText() == "admin") // admin sa nebude dat vymazat
            warningMessage("Nice try :)");
        else
        {
            QString selectedLogin = ui.comboBox_SelectUserToDelete->currentText();

            if (customers.keys().contains(selectedLogin)) // ak je vybrany customer
                customers.remove(selectedLogin);
            else if (premiumCustomers.keys().contains(selectedLogin)) // ak je vybrany premium customer
                premiumCustomers.remove(selectedLogin);
            else if (employees.keys().contains(selectedLogin)) // ak je vybrany employee
                employees.remove(selectedLogin);

            // vymazanie loginu z comboBoxov
            int indexToDelete = ui.comboBox_SelectUserToDelete->currentIndex();
            ui.comboBox_SelectUserToDelete->removeItem(indexToDelete); // comboBox pre delete user
            indexToDelete = ui.comboBox_Users->findText(selectedLogin);
            ui.comboBox_Users->removeItem(indexToDelete); // comboBox na prihlasovanie
            indexToDelete = ui.comboBox_EmployeeSelectUser->findText(selectedLogin);
            ui.comboBox_EmployeeSelectUser->removeItem(indexToDelete); // comboBox pre employee order info

            infoMessage("User \"" + selectedLogin + "\" was deleted");
        }
    }
    else if (reply == QMessageBox::No)
    {

    }
}

void Pharmacy::on_pushButton_DoneDeleting_clicked()
{
    if (ui.groupBox_AdminDeleteUser->isVisible())
        ui.groupBox_AdminDeleteUser->setVisible(false);
}

// groupBox_EmployeeOrderStuff
void Pharmacy::on_comboBox_EmployeeSelectUser_currentIndexChanged(int index)
{
    QString selectedLogin = ui.comboBox_EmployeeSelectUser->currentText();
    ui.tableWidget_EmployeeOrderInfo->clearContents();
    ui.tableWidget_EmployeeOrderInfo->setRowCount(0);

    if (customers.keys().contains(selectedLogin))
    {
        ui.comboBox_EmployeeSelectOrder->clear();
        if (!customers[selectedLogin].getAllOrders().isEmpty())
        {
            ui.checkBox_IsOrderReady->setEnabled(true);
            for (int i = 0; i < customers[selectedLogin].getAllOrders().size(); i++)
            {
                ui.comboBox_EmployeeSelectOrder->addItem(QString::number(customers[selectedLogin].getAllOrders().keys()[i]));
            }
        }
        else if (customers[selectedLogin].getAllOrders().size() == 0)
            ui.checkBox_IsOrderReady->setEnabled(false);
    }
    else if (premiumCustomers.keys().contains(selectedLogin))
    {
        ui.comboBox_EmployeeSelectOrder->clear();
        if (!premiumCustomers[selectedLogin].getAllOrders().isEmpty())
        {
            ui.checkBox_IsOrderReady->setEnabled(true);
            for (int i = 0; i < premiumCustomers[selectedLogin].getAllOrders().size(); i++)
            {
                ui.comboBox_EmployeeSelectOrder->addItem(QString::number(premiumCustomers[selectedLogin].getAllOrders().keys()[i]));
            }
        }
        else if (premiumCustomers[selectedLogin].getAllOrders().size() == 0)
            ui.checkBox_IsOrderReady->setEnabled(false);
    }
}

void Pharmacy::on_comboBox_EmployeeSelectOrder_currentIndexChanged(int index)
{
    QString selectedLogin = ui.comboBox_EmployeeSelectUser->currentText();
    currentOrder = nullptr;

    if (ui.comboBox_EmployeeSelectOrder->currentIndex() != -1)
    {
        unsigned int selectedOrderNum = ui.comboBox_EmployeeSelectOrder->currentText().toUInt();

        if (customers.keys().contains(selectedLogin))
        {
            currentOrder = customers[selectedLogin].getOrder(selectedOrderNum);

            if (currentOrder->isOrderReady()) // ci vybrana objednavka ready
                ui.checkBox_IsOrderReady->setChecked(true);
            else
                ui.checkBox_IsOrderReady->setChecked(false);

            ui.tableWidget_EmployeeOrderInfo->clearContents();

            if (!currentOrder->getOrderedProducts().isEmpty())
            {
                ui.tableWidget_EmployeeOrderInfo->setRowCount(currentOrder->getOrderedProducts().size());
                ui.checkBox_IsOrderReady->setEnabled(true);
                for (int i = 0; i < currentOrder->getOrderedProducts().size(); i++)
                {
                    QTableWidgetItem* name = new QTableWidgetItem();
                    QTableWidgetItem* price = new QTableWidgetItem();

                    name->setText(currentOrder->getOrderedProducts()[i].getProductName());
                    price->setText(QString::number(currentOrder->getOrderedProducts()[i].getPrice(), 'f', 2) + " EUR");
                    ui.tableWidget_EmployeeOrderInfo->setItem(i, 0, name);
                    ui.tableWidget_EmployeeOrderInfo->setItem(i, 1, price);
                }
            }
            else
            {
                ui.checkBox_IsOrderReady->setEnabled(false);
            }
        }
        else if (premiumCustomers.keys().contains(selectedLogin))
        {
            currentOrder = premiumCustomers[selectedLogin].getOrder(selectedOrderNum);

            if (currentOrder->isOrderReady())
                ui.checkBox_IsOrderReady->setChecked(true);
            else
                ui.checkBox_IsOrderReady->setChecked(false);

            ui.tableWidget_EmployeeOrderInfo->clearContents();

            if (!currentOrder->getOrderedProducts().isEmpty())
            {
                ui.tableWidget_EmployeeOrderInfo->setRowCount(currentOrder->getOrderedProducts().size());
                ui.checkBox_IsOrderReady->setEnabled(true);

                for (int i = 0; i < currentOrder->getOrderedProducts().size(); i++)
                {
                    QTableWidgetItem* name = new QTableWidgetItem();
                    QTableWidgetItem* price = new QTableWidgetItem();

                    name->setText(currentOrder->getOrderedProducts()[i].getProductName());
                    double afterDiscount = (1.0 - (double(premiumCustomers[selectedLogin].getDiscount()) / 100)) * currentOrder->getOrderedProducts()[i].getPrice();
                    price->setText(QString::number(afterDiscount, 'f', 2) + " EUR");

                    ui.tableWidget_EmployeeOrderInfo->setItem(i, 0, name);
                    ui.tableWidget_EmployeeOrderInfo->setItem(i, 1, price);
                }
            }
            else
            {
                ui.checkBox_IsOrderReady->setEnabled(false);
            }
        }

    }
}

void Pharmacy::on_pushButton_EmployeeCreateReceipt_clicked()
{
    if (currentOrder == nullptr)
    {
        warningMessage("No order selected");
        return;
    }

    if (currentOrder->getOrderedProducts().isEmpty())
    {
        warningMessage("No products in this order");
        return;
    }

    QString orderNumber = QString::number(currentOrder->getOrderNumber());

    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "Order_" + orderNumber, tr("Txt File (*.txt);;All files (*.)"));

    QFile receipt(fileName);

    if (!receipt.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        warningMessage("Error with creating the receipt");
        return;
    }

    QTextStream out(&receipt);

    time_t now = time(0);
    char* date = ctime(&now);

    out << "Pharmacy Eshop\nDate and time: " << date << "\n******************************\nOrder number: " << orderNumber << "\nBought products:\n";

    for (int i = 0; i < currentOrder->getOrderedProducts().size(); i++)
    {
        out << "1x ... " << currentOrder->getOrderedProducts()[i].getProductName() << ", " << QString::number(currentOrder->getOrderedProducts()[i].getPrice(), 'f', 2) << " EUR\n";
    }

    out << "______________________________\nIn total: " << QString::number(currentOrder->getCost(), 'f', 2) << " EUR";

    receipt.close();

    infoMessage("Receipt created");

}

void Pharmacy::on_checkBox_IsOrderReady_clicked()
{
    if (ui.checkBox_IsOrderReady->isChecked())
        currentOrder->setOrderReady(true);
    else
        currentOrder->setOrderReady(false);
}
