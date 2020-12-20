#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets>

#include "ui_AddCustomerDialog.h"

class AddCustomerDialog : public QDialog
{
	Q_OBJECT

public:
	AddCustomerDialog(QWidget* parent = Q_NULLPTR) : QDialog(parent), addCustomerUI(new Ui::DialogAddCustomer)
	{
		addCustomerUI->setupUi(this);
	}

	QString getName() { return addCustomerUI->lineEdit_Name->text(); }
	QString getSurname() { return addCustomerUI->lineEdit_Surname->text(); }
	QString getAdress() { return addCustomerUI->lineEdit_Adress->text(); }
	QString getLogin() { return addCustomerUI->lineEdit_Login->text(); }
	QString getPassword()
	{
		return QCryptographicHash::hash(addCustomerUI->lineEdit_Password->text().toStdString().c_str(), QCryptographicHash::Sha1).toHex();
	}

private:
	Ui::DialogAddCustomer* addCustomerUI;
};