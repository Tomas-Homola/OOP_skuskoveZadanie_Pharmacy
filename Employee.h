#pragma once

#include "User.h"

class Employee : public User
{
private:
	QString position = "";

public:
	Employee() : User() {}
	Employee(QString position, QString login, QString password) : User(login, password, false) { this->position = position; }

	QString getPosition() { return position; }

	QString whoAmI() { return "Employee"; }

	void setPosition(QString newPosition) { position = newPosition; }

};