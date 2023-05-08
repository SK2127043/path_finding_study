#include "board.h"

bool Board::find(const Point& start, const Point& goal)
{
	Mass* startMass = mass_[start.y()][start.x()];
	Mass* goalMass = mass_[goal.y()][goal.x()];
	
	startMass.setStatus(Mass::START);
	startMass.setList(Mass::OPEN);
	goalMass.setStatus(Mass::GOAL);

	std::sort(values.begin(), values.end(), [](const int& a, const int& b) { return a < b; });
	
	Point p = start;
	while (!open_list.empty()) {
		if(isGoal){
			Mass pMass = mass_[goal.y()][goal.x()];
			while(pMass.prev != ){
				pMass = pMass.prev;
				pMass.setStatus(Mass::WAYPOINT);
				}
		
		if (p != start) mass_[p.x()][p.y()].setStatus(Mass::WAYPOINT);

		
	}

	return false;
}

void Board::show() const 
{
	std::cout << std::endl;

	for (int y = 0; y < BOARD_SIZE; y++) {
		std::cout << " ";
		for (int x = 0; x < BOARD_SIZE; x++) {
			std::cout << "+-";
		}
		std::cout << "+" << std::endl;

		std::cout << " ";
		for (int x = 0; x < BOARD_SIZE; x++) {
			std::cout << "|";
			switch (mass_[y][x].getStatus()) {
			case Mass::BLANK:
				std::cout << " ";
				break;
			case Mass::START:
				std::cout << "S";
				break;
			case Mass::GOAL:
				std::cout << "G";
				break;
			case Mass::WAYPOINT:
				std::cout << "o";
				break;
			case Mass::WALL:
				std::cout << "#";
				break;
			case Mass::WATER:
				std::cout << "~";
				break;
			case Mass::ROAD:
				std::cout << "$";
				break;
			}
		}
		std::cout << "|" << std::endl;
	}

	std::cout << " ";
	for (int x = 0; x < BOARD_SIZE; x++) {
		std::cout << "+-";
	}
	std::cout << "+" << std::endl;

}
