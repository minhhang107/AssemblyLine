// Name: Minh Hang Nguyen
// Seneca Student ID: 166382184
// Seneca email: mhnguyen16@myseneca.ca
// Date of completion: November 26th, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include <string>
#include "Station.h"
#include "Utilities.h"


size_t Station::m_widthField = 0;
int Station::id_generator = 0;
Utilities u;

Station::Station() : m_id{}, m_itemName{}, m_desc{}, m_serialNumber{}, m_quantity{} {};

Station::Station(const std::string& string) {
	size_t pos = 0;
	std::string token;
	bool more = true;


	m_id = ++id_generator;

	m_itemName = u.extractToken(string, pos, more);

	if (more)
		m_serialNumber = stoi(u.extractToken(string, pos, more));

	if (more)
		m_quantity = stoi(u.extractToken(string, pos, more));

	if (more)
		m_desc = string.substr(pos);

	if (u.getFieldWidth() > m_widthField)
		m_widthField = u.getFieldWidth();
};

const std::string& Station::getItemName() const {
	return m_itemName;
};

unsigned int Station::getNextSerialNumber() {
	m_serialNumber++;
	return m_serialNumber - 1;
};

unsigned int Station::getQuantity() const {
	return m_quantity;
};

void Station::updateQuantity() {
	m_quantity--;
	if (m_quantity < 0)
		throw "There is not enough quantity!";
};

void Station::display(std::ostream& os, bool full) const {
	os
		<< std::right << "[" << std::setfill('0') << std::setw(3) << m_id
		<< "] Item: " 
		<< std::left << std::setfill(' ') << std::setw(u.getFieldWidth()) << m_itemName
		<< std::right << " [" << std::setfill('0') << std::setw(6) << m_serialNumber << "]";
	
	if (full) {
		os
			<< std::left << " Quantity: " << std::setfill(' ') << std::setw(u.getFieldWidth()) << m_quantity
			<< " Description: " << m_desc;
	}
	os << std::endl;

};

