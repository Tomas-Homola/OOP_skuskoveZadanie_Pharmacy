#pragma once

#include "User.h"

class Customer : public User
{
protected:
	QString name = "";
	QString surname = "";
	QString adress = "";
	double totalMoneySpent = 0.0;

public:
	Customer() : User() {}
	Customer(QString name, QString surname, QString adress, double totalMoneySpent, QString login, QString password) : User(login, password, false) { this->name = name, this->surname = surname, this->adress = adress; this->totalMoneySpent = totalMoneySpent; }

	QString getName() { return name; }
	QString getSurname() { return surname; }
	QString getAdress() { return adress; }
	double getTotalMoneySpent() { return totalMoneySpent; }

	QString whoAmI() { return "Customer"; }

	void setName(QString newName) { name = newName; }
	void setSurname(QString newSurname) { surname = newSurname; }
	void setAdress(QString newAdress) { adress = newAdress; }

	void info() { qDebug() << name << surname << adress << login << password; }

};