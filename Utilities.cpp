// Name: Minh Hang Nguyen
// Seneca Student ID: 166382184
// Seneca email: mhnguyen16@myseneca.ca
// Date of completion: November 26th, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <iomanip>
#include "Utilities.h"

char Utilities::m_delimiter;

void Utilities::setFieldWidth(size_t newWidth) {
	m_widthField = newWidth;
};

size_t Utilities::getFieldWidth() const {
	return m_widthField;
};

std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
	std::string token;

	if (str[next_pos] != getDelimiter()) {
		size_t end_pos;
		if (str.find(getDelimiter(), next_pos) != std::string::npos) {
			end_pos = str.find(getDelimiter(), next_pos);
			more = true;
		}
		else {
			end_pos = str.find_last_not_of(' ')+1;
			more = false;
		}
		token = str.substr(next_pos, end_pos - next_pos);
		next_pos = end_pos + 1;
		
		if (token.length() > getFieldWidth())
			setFieldWidth(token.length());
	}
	else {
		more = false;
		throw "Invalid token!";
	}
	return token;
};

void Utilities::setDelimiter(char newDelimiter) {
	m_delimiter = newDelimiter;
};

char Utilities::getDelimiter() {
	return m_delimiter;
};
