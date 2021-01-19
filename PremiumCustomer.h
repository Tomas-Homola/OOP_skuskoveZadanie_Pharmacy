#pragma once

#include "Customer.h"

class PremiumCustomer : public Customer
{
private:
	int discount = -1;

public:
	PremiumCustomer() : Customer() {}
	PremiumCustomer(QString name, QString surname, QString adress, double totalMoneySpent, int discount, QString login, QString password) : Customer(name, surname, adress, totalMoneySpent, login, password) { this->discount = discount; }

	int getDiscount() { return discount; }

	QString whoAmI() { return "PremiumCustomer"; }

	void setDicount(int newDiscount) { discount = newDiscount; }

	void info()
	{ 
		qDebug() << name << surname << adress << discount << login << password; 
		for (int i = 0; i < orders.size(); i++)
		{
			qDebug() << "Order number:" << orders.keys()[i];
			orders[orders.keys()[i]].info();
		}
	}

};