#pragma once

#include "Product.h"
//#include <QVector>

class Order
{
private:
	bool isReady = false;
	unsigned int orderNumber = -1;
	QVector<Product> orderedProducts;

public:
	Order() {}
	Order(bool isReady, unsigned int orderNumber) : isReady(isReady), orderNumber(orderNumber) {}

	bool isOrderReady() { return isReady; }
	unsigned int getOrderNumber() { return orderNumber; }

	void setOrderReady(bool isReadyNow) { isReady = isReadyNow; }
	void setOrderNumber(unsigned int newOrderNumber) { orderNumber = newOrderNumber; }
	void addProduct(Product& productToAdd) { orderedProducts.push_back(productToAdd); }
	void removeProduct(int index) { orderedProducts.remove(index); }

	QVector<Product>* getOrderedProducts() { return &orderedProducts; }
	Product* getSpecificProduct(int index) { return &orderedProducts[index]; }

	void info()
	{
		for (int i = 0; i < orderedProducts.size(); i++)
			orderedProducts[i].info();
	}
};