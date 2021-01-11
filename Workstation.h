// Name: Minh Hang Nguyen
// Seneca Student ID: 166382184
// Seneca email: mhnguyen16@myseneca.ca
// Date of completion: November 26th, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef WORKSTATION_H
#define WORKSTATION_H
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

class Workstation: public Station {
	std::deque<CustomerOrder> m_orders{};
	Workstation* m_pNextStation{ nullptr };
public:
	Workstation();
	Workstation(const std::string&);
	Workstation(const Workstation&) = delete;
	Workstation& operator=(const Workstation&) = delete;
	void runProcess(std::ostream&);
	bool moveOrder();
	void setNextStation(Station& station);
	const Workstation* getNextStation() const;
	bool getIfCompleted(CustomerOrder& order);
	void display(std::ostream&);
	Workstation& operator+=(CustomerOrder&&);
};

#endif



