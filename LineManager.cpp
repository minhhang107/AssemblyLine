// Name: Minh Hang Nguyen
// Seneca Student ID: 166382184
// Seneca email: mhnguyen16@myseneca.ca
// Date of completion: November 26th, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <fstream>
#include "LineManager.h"
#include "Station.h"

size_t LineManager::count = 0;

LineManager::LineManager() {};

LineManager::LineManager(const std::string& filename, std::vector<Workstation*>& ws, std::vector<CustomerOrder>& orders) {
	Utilities u;
	std::vector<Workstation*> tempStations;
	std::string string{ "" }, currentStation{ "" }, nextStation{ "" };
	
	std::ifstream file(filename);

	if (!file.is_open()) {
		throw std::string("There was an error opening file: [" + filename + "].");
	}

	while (!file.eof()) {
		size_t pos = 0;
		bool more = true;
		std::getline(file, string);

		// find the name of current and next station
		currentStation = u.extractToken(string, pos, more);
		if (more) {
			nextStation = u.extractToken(string, pos, more);
		}
		else nextStation = "";

		// link the next station to the current one
		for (size_t i = 0; i < ws.size(); i++) {
			if (ws[i]->getItemName() == currentStation) {
				bool found = false;
				for (size_t j = 0; j < ws.size() && found == false; j++) {
					if (ws[j]->getItemName() == nextStation) {
						ws[i]->setNextStation(*(ws[j]));
						found = true;
					}
				}

				// add to the sorted vector
				SortedLine.push_back(ws[i]);
			}
		}
	};
	file.close();

	for (size_t k = 0; k < orders.size(); k++) {
		TobeFilled.push_back(std::move(orders[k]));
	}
	m_cntCustomerOrder = TobeFilled.size();
	AssemblyLine = ws;
};

bool LineManager::run(std::ostream& os) {
	CustomerOrder completedOrder{};
	bool completed = false;

	count++;
	os << "Line Manager Iteration: " << count << std::endl;
	
	if (!TobeFilled.empty()) {
		*(SortedLine[0]) += (std::move(TobeFilled.front()));
		TobeFilled.pop_front();
	}

	for (size_t i = 0; i < AssemblyLine.size(); i++) {
		AssemblyLine[i]->runProcess(os);
	}

	for (size_t j = 0; j < SortedLine.size(); j++) {
		AssemblyLine[j]->moveOrder();
	}

	for (size_t k = 0; k < AssemblyLine.size(); k++) {
		if (AssemblyLine[k]->getIfCompleted(completedOrder))
			Completed.push_back(std::move(completedOrder));
	}
	
	if (Completed.size() == m_cntCustomerOrder)
		completed = true;

	return completed;
};

void LineManager::displayCompletedOrders(std::ostream& os) const {
	for (size_t i = 0; i < Completed.size(); i++) {
		Completed[i].display(os);
	}
};

void LineManager::displayStations() const {
	for (size_t i = 0; i < AssemblyLine.size(); i++) {
		AssemblyLine[i]->display(std::cout);
	}
};

void LineManager::displayStationsSorted() const {
	for (size_t i = 0; i < SortedLine.size(); i++) {
		SortedLine[i]->display(std::cout);
	}
};
