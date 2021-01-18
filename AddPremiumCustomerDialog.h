#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets>

#include "ui_AddPremiumCustomerDialog.h"

class AddPremiumCustomerDialog : public QDialog
{
	Q_OBJECT

public:
	AddPremiumCustomerDialog(QWidget* parent = Q_NULLPTR) : QDialog(parent), addPremiumCustomerUI(new Ui::AddPremiumCustomerDialog)
	{
		addPremiumCustomerUI->setupUi(this);
	}

	QString getName() { return addPremiumCustomerUI->lineEdit_Name->text().trimmed(); }
	QString getSurname() { return addPremiumCustomerUI->lineEdit_Surname->text().trimmed(); }
	QString getAdress() { return addPremiumCustomerUI->lineEdit_Adress->text().trimmed(); }
	int getDiscount() { return addPremiumCustomerUI->spinBox_Discount->value(); }
	QString getLogin() { return addPremiumCustomerUI->lineEdit_Login->text().trimmed(); }
	QString getPassword()
	{
		if (!addPremiumCustomerUI->lineEdit_Password->text().trimmed().isEmpty())
			return QCryptographicHash::hash(addPremiumCustomerUI->lineEdit_Password->text().toUtf8(), QCryptographicHash::Sha1).toHex();
		else
			return QString("");
	}


private:
	Ui::AddPremiumCustomerDialog* addPremiumCustomerUI;

	bool showPassword = false;

private slots:
	void on_checkBox_ShowPassword_clicked()
	{
		if (!showPassword)
		{
			addPremiumCustomerUI->lineEdit_Password->setEchoMode(QLineEdit::Normal);
			showPassword = true;
		}
		else if (showPassword)
		{
			addPremiumCustomerUI->lineEdit_Password->setEchoMode(QLineEdit::Password);
			showPassword = false;
		}
	}
};