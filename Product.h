#pragma once

class Product
{
private:
	int ID = -1;
	QString productName = "";
	QString productDescription = "";
	double price = -1.0;
	int quantity = -1;

public:
	Product() {};
	Product(int ID, QString productName, QString productDescription, double price, int quantity) { this->ID = ID; this->productName = productName; this->productDescription = productDescription; this->price = price; this->quantity = quantity; }

	int getID() { return ID; }
	QString getProductName() { return productName; }
	QString getProductsDescription() { return productDescription; }
	double getPrice() { return price; }
	int getQuantity() { return quantity; }

	void setID(int newID) { ID = newID; }
	void setProductName(QString newProductName) { productName = newProductName; }
	void setProductDescription(QString newProductDescription) { productDescription = newProductDescription; }
	void setPrice(double newPrice) { price = newPrice; }
	void setQuantity(int newQuantity) { quantity = newQuantity; }
	void productBought() { quantity -= 1; }

	void info()
	{
		qDebug() << "ID:" << ID << "Product name:" << productName << "Description:" << productDescription << "Price:" << price << "Quantity:" << quantity << "\n";
	}

};