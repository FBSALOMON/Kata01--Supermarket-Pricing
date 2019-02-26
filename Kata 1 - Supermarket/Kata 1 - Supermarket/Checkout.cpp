#include "pch.h"
#include "Checkout.h"


Checkout::Checkout():total(0)
{

}


Checkout::~Checkout()
{
}

void Checkout::addItemPrice(std::string item, int price) {
	prices[item] = price;
}

void Checkout::addItem(std::string item) {
	std::map<std::string, int>::iterator it = prices.find(item);
	if (it == prices.end()) {
		throw std::invalid_argument("Invalid Item, don't have price");
	}
	items[item]++;
}

void Checkout::addDiscount(std::string item, int nbrOfItems, int discountPrice) {
	Discount discount;
	discount.nbrOfItems = nbrOfItems;
	discount.discountPrice = discountPrice;
	discounts[item] = discount;
}

int Checkout::calculateTotal() {
	total = 0;
	for (std::map<std::string, int>::iterator it = items.begin(); it != items.end(); ++it) {
		std::string item = it->first;
		int itemCount = it->second;
		calculateItem(item, itemCount);
	}
	return total;
}


void Checkout::calculateItem(std::string item, int itemCount) {
	std::map<std::string, Discount>::iterator discoutIterator;
	discoutIterator = discounts.find(item);
	if (discoutIterator != discounts.end()) {
		Discount discount = discoutIterator->second;
		calculateDiscount(item, itemCount, discount);
	}
	else {
		total += itemCount * prices[item];
	}
}

void Checkout::calculateDiscount(std::string item, int itemCount, Discount discount) {
	if (itemCount >= discount.nbrOfItems) {
		int nbrOfDiscounts = itemCount / discount.nbrOfItems;
		total += nbrOfDiscounts * discount.discountPrice;
		int remainingItems = itemCount % discount.nbrOfItems;
		total += remainingItems * prices[item];
	}
	else {
		total += itemCount * prices[item];
	}
}