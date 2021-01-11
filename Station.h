// Name: Minh Hang Nguyen
// Seneca Student ID: 166382184
// Seneca email: mhnguyen16@myseneca.ca
// Date of completion: November 26th, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef STATION_H
#define STATION_H
#include <string>
#include "Utilities.h"

class Station {
	int m_id;
	std::string m_itemName;
	std::string m_desc;
	int m_serialNumber;
	int m_quantity;
	static size_t m_widthField;
	static int id_generator;
public:
	Station();
	Station(const std::string& string);
	const std::string& getItemName() const;
	unsigned int getNextSerialNumber();
	unsigned int getQuantity() const;
	void updateQuantity();
	void display(std::ostream& os, bool full) const;
};

#endif 

