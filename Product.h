#pragma once

class Product
{
private:
	int ID = -1;
	QString productName = "";
	double price = -1.0;
	int quantity = -1;

public:
	Product() {};
	Product(int ID, QString productName, double price, int quantity) { this->ID = ID; this->productName = productName; this->price = price; this->quantity = quantity; }

	int getID() { return ID; }
	QString getProductName() { return productName; }
	double getPrice() { return price; }
	int getQuantity() { return quantity; }

	void setID(int newID) { ID = newID; }
	void setProductName(QString newProductName) { productName = newProductName; }
	void setPrice(double newPrice) { price = newPrice; }
	void setQuantity(int newQuantity) { quantity = newQuantity; }

	void info()
	{
		qDebug() << "ID:" << ID << "Product name:" << productName << "Price:" << price << "Quantity:" << quantity << "\n";
	}

};