#pragma once

#include "Product.h"
//#include <QVector>

class Order // pridat double pre celkovu cenu objednavky
{
private:
	bool isReady = false;
	unsigned int orderNumber = -1;
	double cost = 0.0;
	QVector<Product> orderedProducts;

public:
	Order() {}
	Order(bool isReady, unsigned int orderNumber) : isReady(isReady), orderNumber(orderNumber) {}

	bool isOrderReady() { return isReady; }
	unsigned int getOrderNumber() { return orderNumber; }
	double getCost() { return cost; }

	void setOrderReady(bool isReadyNow) { isReady = isReadyNow; }
	void setOrderNumber(unsigned int newOrderNumber) { orderNumber = newOrderNumber; }
	void addProduct(Product& productToAdd)
	{
		orderedProducts.push_back(productToAdd);
		cost += productToAdd.getPrice();
	}

	void removeProduct(int index)
	{ 
		if (index < orderedProducts.size())
		{
			cost -= orderedProducts[index].getPrice();
			orderedProducts.remove(index);
		}

	}

	QVector<Product>& getOrderedProducts() { return orderedProducts; }
	Product& getSpecificProduct(int index) { return orderedProducts[index]; }

	void info()
	{
		qDebug() << "Order number:" << orderNumber;
		for (int i = 0; i < orderedProducts.size(); i++)
			orderedProducts[i].info();
		qDebug() << "Total cost:" << cost << "EUR\n";
	}
};