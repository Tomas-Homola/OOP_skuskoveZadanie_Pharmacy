#pragma once

#include "Customer.h"

class PremiumCustomer : public Customer
{
private:
	int discount = -1;

public:
	PremiumCustomer() : Customer() {}
	PremiumCustomer(QString name, QString surname, QString adress, int discount, QString login, QString password) : Customer(name, surname, adress, login, password) { this->discount = discount; }

	int getDiscount() { return discount; }

	QString whoAmI() { return "PremiumCustomer"; }

	void setDicount(int newDiscount) { discount = newDiscount; }

};