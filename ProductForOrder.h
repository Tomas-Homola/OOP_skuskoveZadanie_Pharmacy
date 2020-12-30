#pragma once

class ProductForOrder
{
private:
	QString productName = "";
	QString productDescription = "";
	double price = -1.0;

public:
	ProductForOrder() {}
	ProductForOrder(QString productName, QString productDescription, double price) : productName(productName), productDescription(productDescription), price(price) {}

	QString getProductName() { return productName; }
	double getPrice() { return price; }

	void setProductName(QString newProductName) { productName = newProductName; }
	void setPrice(double newPrice) { price = newPrice; }

	void info() { qDebug() << "Product name:" << productName << "Product description:" << productDescription << "Product price:" << price << "EUR\n"; }
};