#include "board.h"
#include <vector>

bool Board::find(const Point& start, const Point& goal)
{
	Mass* startMass = mass_[start.y()][start.x()];
	Mass* goalMass = mass_[goal.y()][goal.x()];
	
	startMass.setStatus(Mass::START);
	startMass.setList(Mass::OPEN);
	open_list.push(startMass);
	startMass->g = 0;
	startMass->h = 3 * (abs(start.x() + goal.x()) + abs(start.y() + goal.y())); //1マス移動するコストは3
	startMass->f = g + h;
	
	goalMass.setStatus(Mass::GOAL);

	std::priority_queue<Mass*, std::vector<Mass*>, delcltype([](Mass *a, Mass *b) { return a->f > b->f; }) > open_list([](Mass *a, Mass *b) { return a->f > b->f; });
	
	Point p = start;
	while (!open_list.empty()) {
		if(mass_[p.x()][p.y()].getStatus() == Mass::GOAL){  //ゴールが見つかった場合、経路のstatusをWAYPOINTにする
			Mass* pMass = mass_[goal.y()][goal.x()];
			while(pMass->prev != NULL){
				pMass = pMass->prev;
				pMass->setStatus(Mass::WAYPOINT);
				}
			return true;
		}
		
		 open_list.top
		mass_[np_x][np_y].setStatus(Mass::CLOSED);
		open_list.pop();
		
		for(int i_x = -1; i_x <=1; i_x++){
			for(int i_y = -1; i_y <=1; i_y++){
				if(abs(i_x + i_y) != 1) continue;  //4方向のみの探索
				int np_x = p.x() + i_x;
				int np_y = p.y() + i_y;
				if(mass_[np_x][np_y].getStatus() == Mass::WALL || (np_x < 0 || np_x > 10) || (np_y < 0 || np_y > 10))  continue;
				if(mass_[np_x][np_y].getList() == Mass::CLOSED) continue;
				
				int newG = mass_[p.x()][p.y()].f;
				if(mass_[p.x()][p.y()].getStatus() == Mass::WATER) newG += 9;
				else if(mass_[p.x()][p.y()].getStatus() == Mass::ROAD) newG += 1;
				else newG + 3;
				
				if(mass_[np_x][np_y].getList() == Mass::OPEN && mass_[np_x][np_y].g =< newG) continue;
				else if(mass_[np_x][np_y].getList() == Mass::NONE) {
					mass_[np_x][np_y].setList(Mass::OPEN);
					open_list.push(mass_[np_x][np_y]);
				}
				mass_[np_x][np_y].g = newG;
					
					
					

		
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
