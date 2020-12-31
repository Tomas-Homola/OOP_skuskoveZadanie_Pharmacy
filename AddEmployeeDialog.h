#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets>

#include <ui_AddEmployeeDialog.h>

class AddEmployeeDialog : public QDialog
{
	Q_OBJECT

public:
	AddEmployeeDialog(QWidget* parent = Q_NULLPTR) : QDialog(parent), addEmployeeUI(new Ui::AddEmployeeDialog)
	{
		addEmployeeUI->setupUi(this);
	}

	QString getPosition() { return addEmployeeUI->lineEdit_Position->text().trimmed(); }
	QString getLogin() { return addEmployeeUI->lineEdit_Login->text().trimmed(); }
	QString getPassword()
	{
		if (!addEmployeeUI->lineEdit_Password->text().trimmed().isEmpty())
			return QCryptographicHash::hash(addEmployeeUI->lineEdit_Password->text().toStdString().c_str(), QCryptographicHash::Sha1).toHex();
		else
			return QString("");
	}

private:
	Ui::AddEmployeeDialog* addEmployeeUI;

	bool showPassword = false;

private slots:
	void on_checkBox_ShowPassword_clicked()
	{
		if (!showPassword)
		{
			addEmployeeUI->lineEdit_Password->setEchoMode(QLineEdit::Normal);
			showPassword = true;
		}
		else if (showPassword)
		{
			addEmployeeUI->lineEdit_Password->setEchoMode(QLineEdit::Password);
			showPassword = false;
		}
	}
};