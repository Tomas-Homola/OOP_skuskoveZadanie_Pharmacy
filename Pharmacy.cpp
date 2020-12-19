#include "Pharmacy.h"

/*
QString adminPassword = "adminpassword";
    qDebug() << "Before encryption:" << adminPassword << "\n";

    QString encrypted1 = QCryptographicHash::hash(adminPassword.toStdString().c_str(), QCryptographicHash::Sha1).toHex();
    QString encrypted2 = QCryptographicHash::hash(adminPassword.toStdString().c_str(), QCryptographicHash::Sha1).toHex();

    qDebug() << "After encryption1" << encrypted1;
    qDebug() << "After encryption2" << encrypted2;

*/

Pharmacy::Pharmacy(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    ui.groupBox_Login->setVisible(false);

    ui.comboBox_users->addItem("admin");

}

void Pharmacy::on_pushButton_SignInWindow_clicked()
{
    ui.groupBox_Login->setVisible(true);
}

void Pharmacy::on_pushButton_SignInConfirm_clicked()
{
    qDebug() << "Login:" << ui.comboBox_users->currentText();
    qDebug() << "Password:" << ui.lineEdit_Password->text();

    qDebug() << QCryptographicHash::hash(ui.lineEdit_Password->text().toStdString().c_str(), QCryptographicHash::Sha1).toHex();

    ui.groupBox_Login->setVisible(false);
}