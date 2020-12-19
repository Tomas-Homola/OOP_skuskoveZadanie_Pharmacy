#pragma once

#include "User.h"

class Admin : protected User
{
private:


public:
	Admin() : User() {}
	Admin(QString login, QString password) : User(login, password, true) {};

	QString whoAmI() { return "Admin"; }

};