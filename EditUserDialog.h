#pragma once

#include <QtWidgets\QDialog>
#include <QtWidgets>

#include <ui_EditUserDialog.h>

class EditUserDialog : public QDialog
{
	Q_OBJECT

private:
	Ui::EditUserDialog* editUserUI;

	QList<QString> customers;
	QList<QString> premiumCustomers;
	QList<QString> employees;

	bool showPassword = false;

public:
	// myslienka do buducnosti: poslat sem smernik na QMapy pre uzivatelov a potom pri vybere daneho uzivatela dopisat do lineEditov aktualne informacie a po accepted() ak sa nove informacie nerovnaju starym, tak sa zmenia
	EditUserDialog(QString userType, QList<QString>& customers, QList<QString>& premiumCustomers, QList<QString>& employees, QWidget* parent = Q_NULLPTR) : QDialog(parent), editUserUI(new Ui::EditUserDialog), customers(customers), premiumCustomers(premiumCustomers), employees(employees)
	{
		editUserUI->setupUi(this);
		
		if (userType == "Customer")
		{
			customerUISettings(false);
			editUserUI->groupBox_UserSelect->setVisible(false);
		}
		else if (userType == "PremiumCustomer")
		{
			premiumCustomerUISettings(false);
			editUserUI->groupBox_UserSelect->setVisible(false);
		}
		else if (userType == "Employee")
		{
			employeeUISettings(false);
			editUserUI->groupBox_UserSelect->setVisible(false);
		}
		else if (userType == "Admin")
		{
			// pridanie loginov do comboBoxu
			for (int i = 0; i < customers.size(); i++)
				editUserUI->comboBox_UserToEdit->addItem(customers[i]);
			for (int i = 0; i < premiumCustomers.size(); i++)
				editUserUI->comboBox_UserToEdit->addItem(premiumCustomers[i]);
			for (int i = 0; i < employees.size(); i++)
				editUserUI->comboBox_UserToEdit->addItem(employees[i]);

			// nastavenie UI podla toho, aky login je ako prvy nastaveny
			QString currentLoginSelected = editUserUI->comboBox_UserToEdit->currentText();
			if (customers.contains(currentLoginSelected))
				customerUISettings(true);
			else if (premiumCustomers.contains(currentLoginSelected))
				premiumCustomerUISettings(true);
			else if (employees.contains(currentLoginSelected))
				employeeUISettings(true);
		}
	}

	// UI settings
	void customerUISettings(bool isAdminSigned)
	{
		if (isAdminSigned) // vsetko okrem discount a position
		{
			editUserUI->label_Name->setVisible(true); // name
			editUserUI->lineEdit_Name->setVisible(true);

			editUserUI->label_Surname->setVisible(true); // surname
			editUserUI->lineEdit_Surname->setVisible(true);

			editUserUI->label_Adress->setVisible(true); // adress
			editUserUI->lineEdit_Adress->setVisible(true);

			editUserUI->label_Discount->setVisible(false); // discount
			editUserUI->spinBox_Discount->setVisible(false);

			editUserUI->label_Position->setVisible(false); // position
			editUserUI->lineEdit_Position->setVisible(false);

			editUserUI->label_Login->setVisible(true); // login
			editUserUI->lineEdit_Login->setVisible(true);

			editUserUI->label_Password->setVisible(true); // password
			editUserUI->lineEdit_Password->setVisible(true);

			editUserUI->checkBox_ShowPassword->setVisible(true); // show password
		}
		else
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
	}
	void premiumCustomerUISettings(bool isAdminSigned)
	{
		if (isAdminSigned) // vsetko okrem position
		{
			editUserUI->label_Name->setVisible(true); // name
			editUserUI->lineEdit_Name->setVisible(true);

			editUserUI->label_Surname->setVisible(true); // surname
			editUserUI->lineEdit_Surname->setVisible(true);

			editUserUI->label_Adress->setVisible(true); // adress
			editUserUI->lineEdit_Adress->setVisible(true);

			editUserUI->label_Discount->setVisible(true); // discount
			editUserUI->spinBox_Discount->setVisible(true);

			editUserUI->label_Position->setVisible(false); // position
			editUserUI->lineEdit_Position->setVisible(false);

			editUserUI->label_Login->setVisible(true); // login
			editUserUI->lineEdit_Login->setVisible(true);

			editUserUI->label_Password->setVisible(true); // password
			editUserUI->lineEdit_Password->setVisible(true);

			editUserUI->checkBox_ShowPassword->setVisible(true); // show password
		}
		else
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
	}
	void employeeUISettings(bool isAdminSigned)
	{
		if (isAdminSigned)
		{
			editUserUI->label_Name->setVisible(false); // name
			editUserUI->lineEdit_Name->setVisible(false);

			editUserUI->label_Surname->setVisible(false); // surname
			editUserUI->lineEdit_Surname->setVisible(false);

			editUserUI->label_Adress->setVisible(false); // adress
			editUserUI->lineEdit_Adress->setVisible(false);

			editUserUI->label_Discount->setVisible(false); // discount
			editUserUI->spinBox_Discount->setVisible(false);

			editUserUI->label_Position->setVisible(true); // psoition
			editUserUI->lineEdit_Position->setVisible(true);

			editUserUI->label_Login->setVisible(true); // login
			editUserUI->lineEdit_Login->setVisible(true);

			editUserUI->label_Password->setVisible(true); // password
			editUserUI->lineEdit_Password->setVisible(true);

			editUserUI->checkBox_ShowPassword->setVisible(true); // show password
		}
		else
		{
			editUserUI->label_Name->setVisible(false); // name
			editUserUI->lineEdit_Name->setVisible(false);

			editUserUI->label_Surname->setVisible(false); // surname
			editUserUI->lineEdit_Surname->setVisible(false);

			editUserUI->label_Adress->setVisible(false); // adress
			editUserUI->lineEdit_Adress->setVisible(false);

			editUserUI->label_Discount->setVisible(false); // discount
			editUserUI->spinBox_Discount->setVisible(false);

			editUserUI->label_Position->setVisible(true); // psoition
			editUserUI->lineEdit_Position->setVisible(true);

			editUserUI->label_Login->setVisible(false); // login
			editUserUI->lineEdit_Login->setVisible(false);

			editUserUI->label_Password->setVisible(false); // password
			editUserUI->lineEdit_Password->setVisible(false);

			editUserUI->checkBox_ShowPassword->setVisible(false); // show password
		}
	}

	// get functions
	QString getName() { return editUserUI->lineEdit_Name->text().trimmed(); }
	QString getSurname() { return editUserUI->lineEdit_Surname->text().trimmed(); }
	QString getAdress() { return editUserUI->lineEdit_Adress->text().trimmed(); }
	int getDiscount() { return editUserUI->spinBox_Discount->value(); }
	QString getPosition() { return editUserUI->lineEdit_Position->text().trimmed(); }
	QString getLogin() { return editUserUI->lineEdit_Login->text().trimmed(); }
	QString getPassword()
	{
		if (!editUserUI->lineEdit_Password->text().isEmpty())
			return QCryptographicHash::hash(editUserUI->lineEdit_Password->text().trimmed().toStdString().c_str(), QCryptographicHash::Sha1).toHex();
		else
			return QString("");
	}

	QString getCurrentLogin() { return editUserUI->comboBox_UserToEdit->currentText(); }

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
	void on_comboBox_UserToEdit_currentIndexChanged(int index)
	{
		QString currentLoginSelected = editUserUI->comboBox_UserToEdit->currentText();

		if (customers.contains(currentLoginSelected))
			customerUISettings(true);
		else if (premiumCustomers.contains(currentLoginSelected))
			premiumCustomerUISettings(true);
		else if (employees.contains(currentLoginSelected))
			employeeUISettings(true);
	}
};