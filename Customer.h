#pragma once

#include "User.h"
#include "Order.h"

class Customer : public User
{
protected:
	QString name = "";
	QString surname = "";
	QString adress = "";
	double totalMoneySpent = 0.0;
	QMap<unsigned int, Order> orders;

public:
	Customer() : User() {}
	Customer(QString name, QString surname, QString adress, double totalMoneySpent, QString login, QString password) : User(login, password, false), name(name), surname(surname), adress(adress), totalMoneySpent(totalMoneySpent) {}

	QString getName() { return name; }
	QString getSurname() { return surname; }
	QString getAdress() { return adress; }
	double getTotalMoneySpent() { return totalMoneySpent; }
	QMap<unsigned int, Order>& getAllOrders() { return orders; }
	Order* getOrder(unsigned int orderNumber) { return &orders[orderNumber]; }
	int getNumOfOrders() { return orders.size(); }

	QString whoAmI() { return "Customer"; }

	void setName(QString newName) { name = newName; }
	void setSurname(QString newSurname) { surname = newSurname; }
	void setAdress(QString newAdress) { adress = newAdress; }
	void addOrder(bool isReady, unsigned int newOrderNumber) { orders[newOrderNumber] = Order(isReady, newOrderNumber); }
	void removeOrder(unsigned int orderNumber) { orders.remove(orderNumber); }

	virtual void info() 
	{ 
		qDebug() << name << surname << adress << login << password;
		for (int i = 0; i < orders.size(); i++)
		{
			orders[orders.keys()[i]].info();
		}
	
	}

};