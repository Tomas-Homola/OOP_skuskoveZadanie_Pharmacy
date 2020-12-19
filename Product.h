#pragma once

#include <qstring.h>

class Product
{
private:
	int ID = -1;
	QString productName = "";
	int quantity = -1;
	double price = -1.0;

public:
	Product() {};
	Product(int ID, QString productName, int quantity, double price) { this->ID = ID; this->productName = productName; this->quantity = quantity; this->price = price; }

	int getID() { return ID; }
	QString getProductName() { return productName; }
	int getQuantity() { return quantity; }
	double getPrice() { return price; }

	void setID(int newID) { ID = newID; }
	void setProductName(QString newProductName) { productName = newProductName; }
	void setQuantity(int newQuantity) { quantity = newQuantity; }
	void setPrice(double newPrice) { price = newPrice; }

};