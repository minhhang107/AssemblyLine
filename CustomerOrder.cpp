// Name: Minh Hang Nguyen
// Seneca Student ID: 166382184
// Seneca email: mhnguyen16@myseneca.ca
// Date of completion: November 26th, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include <algorithm>
#include "CustomerOrder.h"
#include "Utilities.h"


size_t CustomerOrder::m_widthField = 0;

CustomerOrder::CustomerOrder() {};
CustomerOrder::CustomerOrder(std::string& src) {
	Utilities u;
	size_t pos = 0;
	bool more = true;
	m_cntItem = 0;
	m_lstItem = {};

	m_name = u.extractToken(src, pos, more);
	m_product = u.extractToken(src, pos, more);

	size_t startPos = pos;
	while (src.find(u.getDelimiter(),startPos) && startPos != 0) {
		m_cntItem++;
		startPos = src.find(u.getDelimiter(), startPos) + 1;
	}
	m_lstItem = new Item * [m_cntItem];

	for (size_t i = 0; i < m_cntItem; i++) {
		std::string itemName = u.extractToken(src, pos, more);
		m_lstItem[i] = new Item(itemName);
	}
	
	if (m_widthField < u.getFieldWidth())
	m_widthField = u.getFieldWidth();
};

CustomerOrder::CustomerOrder(const CustomerOrder&) {
	throw "Cannot copy order";
};

CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
	*this = std::move(src);
};

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
	if (this != &src) {
		if (m_lstItem) {
			for (size_t i = 0; i < m_cntItem; i++)
				delete m_lstItem[i];
			delete[] m_lstItem;
		}
		
		m_name = src.m_name;
		m_product = src.m_product;
		m_cntItem = src.m_cntItem;
		m_lstItem = src.m_lstItem;

		src.m_name = "";
		src.m_product = "";
		src.m_cntItem = 0;
		src.m_lstItem = nullptr;
	}
	return *this;
};

CustomerOrder::~CustomerOrder() {
	for (size_t i = 0; i < m_cntItem; i++) {
		delete m_lstItem[i];
	}
	delete[] m_lstItem;
};

bool CustomerOrder::isOrderFilled() const {
	bool filled = true;

	for (size_t i = 0; i < m_cntItem && filled == true; i++) {
		if (!m_lstItem[i]->m_isFilled)
			filled = false;
	}
	return filled;
};

bool CustomerOrder::isItemFilled(const std::string& itemName) const {
	bool found = false;
	size_t index;
	for (size_t i = 0; i < m_cntItem && found == false; i++) {
		if (m_lstItem[i]->m_itemName == itemName)
		{
			index = i;
			found = true;
		}
	}
	if (found)
		return m_lstItem[index]->m_isFilled;
	else
		return true;
};

void CustomerOrder::fillItem(Station& station, std::ostream& os) {
	for (size_t i = 0; i < m_cntItem; i++) {
		if (m_lstItem[i]->m_itemName == station.getItemName())
		{
			if (station.getQuantity() > 0)
			{
				station.updateQuantity();
				m_lstItem[i]->m_isFilled = true;
				m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
				os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
			}
			else
				os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
		}
	}
};

void CustomerOrder::display(std::ostream& os) const {
	os << m_name << " - " << m_product << std::endl;
	for (size_t i = 0; i < m_cntItem; i++) {
		os
			<< "[" << std::right << std::setfill('0') << std::setw(6) << m_lstItem[i]->m_serialNumber << "] "
			<< std::left << std::setfill(' ') << std::setw(m_widthField) << m_lstItem[i]->m_itemName << " - "
			<< (m_lstItem[i]->m_isFilled ? "FILLED" : "MISSING") << std::endl;
	}
};