#pragma once

#include <QtWidgets\QDialog>
#include <QtWidgets>

#include <ui_EditUserDialog.h>

class EditUserDialog : public QDialog
{
	Q_OBJECT

private:
	Ui::EditUserDialog* editUserUI;

	bool showPassword = false;

public:
	// este dorobit pre admina: pridat aj comboBox (podobne ako pri prihlasovani)
	EditUserDialog(QString userType, QWidget* parent = Q_NULLPTR) : QDialog(parent), editUserUI(new Ui::EditUserDialog)
	{
		editUserUI->setupUi(this);
		
		if (userType == "Customer")
		{
			customerUISettings();
		}
		else if (userType == "PremiumCustomer")
		{
			premiumCustomerUISettings();
		}
		else if (userType == "Employee")
		{
			employeeUISettings();
		}
	}

	// UI settings
	void customerUISettings()
	{
		editUserUI->label_Discount->setVisible(false); // discount
		editUserUI->spinBox_Discount->setVisible(false);

		editUserUI->label_Position->setVisible(false); // position
		editUserUI->lineEdit_Position->setVisible(false);

		editUserUI->label_Login->setVisible(false); // login
		editUserUI->lineEdit_Login->setVisible(false);

		editUserUI->label_Password->setVisible(false); // password
		editUserUI->lineEdit_Password->setVisible(false);

		editUserUI->checkBox_ShowPassword->setVisible(false); // show password
	}
	void premiumCustomerUISettings()
	{
		editUserUI->label_Discount->setVisible(false); // discount
		editUserUI->spinBox_Discount->setVisible(false);

		editUserUI->label_Position->setVisible(false); // position
		editUserUI->lineEdit_Position->setVisible(false);

		editUserUI->label_Login->setVisible(false); // login
		editUserUI->lineEdit_Login->setVisible(false);

		editUserUI->label_Password->setVisible(false); // password
		editUserUI->lineEdit_Password->setVisible(false);

		editUserUI->checkBox_ShowPassword->setVisible(false); // show password
	}
	void employeeUISettings()
	{
		editUserUI->label_Name->setVisible(false); // name
		editUserUI->lineEdit_Name->setVisible(false);

		editUserUI->label_Surname->setVisible(false); // surname
		editUserUI->lineEdit_Surname->setVisible(false);

		editUserUI->label_Adress->setVisible(false); // adress
		editUserUI->lineEdit_Adress->setVisible(false);

		editUserUI->label_Discount->setVisible(false); // discount
		editUserUI->spinBox_Discount->setVisible(false);

		editUserUI->label_Login->setVisible(false); // login
		editUserUI->lineEdit_Login->setVisible(false);

		editUserUI->label_Password->setVisible(false); // password
		editUserUI->lineEdit_Password->setVisible(false);

		editUserUI->checkBox_ShowPassword->setVisible(false); // show password
	}
	void adminUISettings()
	{

	}

	// get functions
	QString getName() { return editUserUI->lineEdit_Name->text(); }
	QString getSurname() { return editUserUI->lineEdit_Surname->text(); }
	QString getAdress() { return editUserUI->lineEdit_Adress->text(); }
	int getDiscount() { return editUserUI->spinBox_Discount->value(); }
	QString getPosition() { return editUserUI->lineEdit_Position->text(); }
	QString getLogin() { return editUserUI->lineEdit_Login->text(); }
	QString getPassword() { return QCryptographicHash::hash(editUserUI->lineEdit_Password->text().toStdString().c_str(), QCryptographicHash::Sha1).toHex(); }

private slots:
	void on_checkBox_ShowPassword_clicked()
	{
		if (!showPassword)
		{
			editUserUI->lineEdit_Password->setEchoMode(QLineEdit::Normal);
			showPassword = true;
		}
		else if (showPassword)
		{
			editUserUI->lineEdit_Password->setEchoMode(QLineEdit::Password);
			showPassword = false;
		}
	}
};