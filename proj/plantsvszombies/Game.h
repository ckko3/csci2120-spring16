#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <utility>
#include "Homeowner.h"
#include "ZombieArmy.h"
#include "Creature.h"
using namespace std;

class Game {
public:
	Game();
	void startGame();
	void menu();
	void newGame();
	void endRound();
	void endGame();
	void printBoard() const;
	void pressToContinue() const;
	void collectOccupied();
	void clearOccupied();
	void growPlants(char p, pair <int, int> pos);
	void produceZombies(char p, pair <int, int> pos);
	void printEventMsg();
private:
	static const int roundMax = 10;
	static const int sunGain = 2;
	static const int coinGain = 2;
	bool gameEnd;
	int round;
	Homeowner *homeowner;
	ZombieArmy *zombiearmy;
	Creature *board[6][10];
	vector <pair <int, int>> occupiedList;
	struct plantCost {
		char id;
		string name;
		int cost;
	};
	vector <plantCost> plantCostList;
	struct zombieCost {
		char id;
		string name;
		int cost;
	};
	vector <zombieCost> zombieCostList;
	vector <string> eventMsg;
};
#endif // GAME_H
