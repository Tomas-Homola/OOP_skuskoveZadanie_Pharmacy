#pragma once

#include "ProductForOrder.h"
//#include <QVector>

class Order
{
private:
	bool isReady = false;
	unsigned int orderNumber = -1;
	QVector<ProductForOrder> orderedProducts;

public:
	Order() {}
	Order(bool isReady, unsigned int orderNumber) : isReady(isReady), orderNumber(orderNumber) {}

	bool isOrderReady() { return isReady; }
	unsigned int getOrderNumber() { return orderNumber; }

	void setOrderReady(bool isReadyNow) { isReady = isReadyNow; }
	void setOrderNumber(unsigned int newOrderNumber) { orderNumber = newOrderNumber; }
	void addProduct(ProductForOrder& productToAdd) { orderedProducts.push_back(productToAdd); }
	void removeProduct(int index) { orderedProducts.remove(index); }

	QVector<ProductForOrder>& getOrderedProducts() { return orderedProducts; }

	void info()
	{
		for (int i = 0; i < orderedProducts.size(); i++)
			orderedProducts[i].info();
	}
};