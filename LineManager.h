// Name: Minh Hang Nguyen
// Seneca Student ID: 166382184
// Seneca email: mhnguyen16@myseneca.ca
// Date of completion: November 26th, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef LINEMANAGER_H
#define LINEMANAGER_H
#include <vector>
#include <deque>
#include "CustomerOrder.h"
#include "Workstation.h"

class LineManager {
	std::vector<Workstation*> AssemblyLine{};
	std::deque<CustomerOrder> TobeFilled{};
	std::deque<CustomerOrder> Completed{};
	std::vector<Workstation*>SortedLine{};
	unsigned int m_cntCustomerOrder = 0u;
	static size_t count;
public:
	LineManager();
	LineManager(const std::string&, std::vector<Workstation*>&, std::vector<CustomerOrder>&);
	bool run(std::ostream& os);
	/*size_t findFirstStation();*/
	void displayCompletedOrders(std::ostream& os) const;
	void displayStations() const;
	void displayStationsSorted() const;
};

#endif 

