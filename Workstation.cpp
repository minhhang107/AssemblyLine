// Name: Minh Hang Nguyen
// Seneca Student ID: 166382184
// Seneca email: mhnguyen16@myseneca.ca
// Date of completion: November 26th, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include "Workstation.h"

Workstation::Workstation() {};

Workstation::Workstation(const std::string& str) : Station(str) {
	m_pNextStation = nullptr;
};

void Workstation::runProcess(std::ostream& os) {
	if (!m_orders.empty())
		m_orders.front().fillItem(*this, os);
};

bool Workstation::moveOrder() {
	bool isMoving = false;
	if (!m_orders.empty()) {
		if (m_orders.front().isItemFilled(getItemName()) && m_pNextStation)
			isMoving = true;
	}

	if (isMoving) {
		*m_pNextStation += std::move(m_orders.front());
		m_orders.pop_front();
	}
	return isMoving;
};

void Workstation::setNextStation(Station& station) {
	m_pNextStation = static_cast<Workstation*>(&station);
};

const Workstation* Workstation::getNextStation() const {
	return m_pNextStation;
};

bool Workstation::getIfCompleted(CustomerOrder& order) {
	bool isCompleted = false;
	if (!m_orders.empty()) {
		if (m_orders.front().isOrderFilled()) {
			order = std::move(m_orders.front());
			m_orders.pop_front();
			isCompleted = true;
		}
	}
	return isCompleted;
};

void Workstation::display(std::ostream& os) {
	if (m_pNextStation) {
		os << this->getItemName() << " --> " << m_pNextStation->getItemName() << std::endl;
	}
	else {
		os << this->getItemName() << " --> END OF LINE" << std::endl;
	}
};

Workstation& Workstation::operator+=(CustomerOrder&& order) {
	m_orders.push_back(std::move(order));
	return *this;
};
