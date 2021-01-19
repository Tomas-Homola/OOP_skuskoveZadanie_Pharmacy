#pragma once

class Admin
{
private:
	QString login = "admin";
	QString password = "";
	bool isAdmin = true;

public:
	Admin() {};
	Admin(QString password) : login("admin"), password(password), isAdmin(true) {}

	QString getLogin() { return login; }
	QString getPassword() { return password; }
	bool isUserAdmin() { return isAdmin; }

	void setPassword(QString newPassword) { password = newPassword; }

	QString whoAmI() { return "Admin"; }

};