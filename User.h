#pragma once
#include <qstring.h>

class User
{
protected:
	QString login = "";
	QString password = "";
	
	bool isAdmin = false;
public:
	User() {};
	User(QString login, QString password, bool isAdmin) : login(login), password(password), isAdmin(isAdmin) {}
	
	QString getLogin() { return login; }
	QString getPassword() { return password; }
	bool isUserAdmin() { return isAdmin; }

	void setLogin(QString newLogin) { login = newLogin; }
	void setPassword(QString newPassword) { password = newPassword; }

};