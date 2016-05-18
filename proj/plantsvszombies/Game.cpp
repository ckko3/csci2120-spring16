#include <iostream>
#include <conio.h>	// _getch
#include <cctype>	// isalpha
#include <cstdlib>	// exit
#include <iomanip>	// setw
#include <algorithm>	// max
#include "Game.h"
#include "Peashooter.h"
#include "BonkChoy.h"
#include "Threepeater.h"
#include "Wallnut.h"
#include "Sunflower.h"
#include "BasicZombie.h"
#include "Buckethead.h"
#include "Football.h"
#include "Conehead.h"
using namespace std;

// constructor
Game::Game() {
	round = 1;
	gameEnd = false;
	plantCostList.push_back({ '1', "Peashooter (PS)", 1 });
	plantCostList.push_back({ '2', "Bonk Choy (BC)", 3 });
	plantCostList.push_back({ '3', "Treepeater (TP)", 5 });
	plantCostList.push_back({ '4', "Wall-nut (WN)", 3 });
	plantCostList.push_back({ '5', "Sunflower (SF)", 1 });
	zombieCostList.push_back({ '1', "Basic Zombie (BZ)", 1 });
	zombieCostList.push_back({ '2', "Buckethead (BH)", 5 });
	zombieCostList.push_back({ '3', "Football (FB)", 5, });
	zombieCostList.push_back({ '4', "Conehead (CH)", 3 });
}

/* start game */
void Game::startGame() {
	/* display game menu */
	menu();
}

void Game::menu() {
	system("cls");
	cout << "Plants vs Zombies" << endl;
	cout << "1. New Game" << endl;
	cout << "2. Exit" << endl;
	// input for menu
	char m;
	// ignore invalid input
	do {
		m = _getch();
	} while (!(m == '1' || m == '2'));

	 if (m == '2') {
		// exit
		 system("cls");
		 exit (0);
	}
	else {
		newGame();
	}
}

/* New Game */
void Game::newGame() {
	system("cls");
	// ask name
	string name;
	bool validName = false;

	do {
		cout << "Please input your name:" << endl;
		getline(cin, name);

		for (int i = 0; i < (int)name.length(); i++) {
			if (isalpha(name[i])) {
				validName = true;
				break;
			}
		}
		system("cls");

		if (!validName)
			cout << "Invalid player name! Your name should contain at least one alphabet." << endl;

	} while (!validName);

	// which role to play
	cout << "Which role to play?" << endl;
	cout << "1. Homeowner" << endl;
	cout << "2. Zombie Army" << endl;
	// input for role
	char role;
	// ignore invalid input
	do {
		role = _getch();
	} while (!(role == '1' || role == '2'));


	// create Homeowner and ZombieArmy object
	if (role == '1') {
		homeowner = new Homeowner(name, 1);  // human play as homeowner
		zombiearmy = new ZombieArmy("Computer", 2); // computer play as zombie army
	}
	else {
		homeowner = new Homeowner("Computer",2);  // human play as zombie army
		zombiearmy = new ZombieArmy(name,1); // computer play as homeowner
	}

	/* game loop */
	do {
		// Homeowner turn
		while (1) {
			system("cls");
			cout << "Round " << round;
			if (round == roundMax) cout << " (Last Round)";
			cout << endl;
			cout << "Homeowner Turn" << endl;
			printBoard();
			clearOccupied();
			collectOccupied();
			char plant = homeowner->getMove(occupiedList);
			if (plant != '6') {
				// grow plant
				pair <int, int> position = homeowner->getPosition(plant, occupiedList);
				growPlants(plant, position);
			}
			else
				// Do not grow plants
				break;
		}

		// Zombie Army turn
		while (1) {
			system("cls");
			cout << "Round " << round;
			if (round == roundMax) cout << " (Last Round)";
			cout << endl;
			cout << "Zombie Army Turn" << endl;
			printBoard();
			clearOccupied();
			collectOccupied();
			char zombie = zombiearmy->getMove(occupiedList);
			if (zombie != '5') {
				// produce zombies
				pair <int, int> position = zombiearmy->getPosition(zombie, occupiedList);
				produceZombies(zombie, position);
			}
			else
				// Do not produce zombies
				break;
		}

		// End turn
		endRound();
	} while (!gameEnd);

	// End of game
	endGame();
	
}

void Game::printBoard() const {
	// print Homeowner status, board, ZombieArmy status
	cout << setw(10) << "";
	cout << "-------------------------------------------------------------" << endl;
	for (int i = 0; i < 6; i++) {
		// print rows of showing abbr
		cout << setw(10) << left;
		if (i == 2)
			cout << "Homeowner";
		else
			cout << "";
		cout << "|";
		for (int j = 0; j < 10; j++) {
			cout << setw(5) << left;
			if (board[i][j]) {
				if (dynamic_cast<Plant*>(board[i][j]))
					cout << "P:" + board[i][j]->getAbbr();
				else
					cout << "Z:" + board[i][j]->getAbbr();
			}
			else
				cout << "";
			cout << "|";
		}
		if (i == 2)
			cout << " " << "Zombie Army";
		cout << endl;
		// print rows of showing HP
		cout << setw(10) << left;
		if (i == 2)
			cout << "HP: " + to_string(homeowner->getHP());
		else
			cout << "";
		cout << "|";
		for (int k = 0; k < 10; k++) {
			cout << setw(5) << left;
			if (board[i][k])
				cout << "HP:" + to_string(board[i][k]->getHP());
			else
				cout << "";
			cout << "|";
		}
		if (i == 2)
			cout << " " << "Coin: " + to_string(zombiearmy->getCoin());
		cout << endl;
		// print remaining rows
		cout << setw(10) << left;
		if (i == 2)
			cout << "Sun: " + to_string(homeowner->getSun());
		else
			cout << "";
		cout << "-------------------------------------------------------------" << endl;
	}
  
}

void Game::endRound() {
	eventMsg.clear();
	system("cls");
	cout << "End of Round " << round << endl;

	// Event: Homeowner gains sun, Zombie Army gains coin
	homeowner->setSun(homeowner->getSun() + sunGain);
	eventMsg.push_back("Homeowner gained " + to_string(sunGain) + " sun.");
	zombiearmy->setCoin(zombiearmy->getCoin() + coinGain);
	eventMsg.push_back("Zombie Army gained " + to_string(coinGain) + " coin.");

	// Event: possible actions by all creatures
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 10; j++) {
			if (board[i][j]) {
				Zombie* zombiePtr;
				if (zombiePtr = dynamic_cast<Zombie*>(board[i][j])) {
					// Zombie can attack plant/Homeowner or move
					if (j == 0) {
						// attack Homeowner
						homeowner->setHP(homeowner->getHP() - board[i][j]->getDamage());
						eventMsg.push_back(board[i][j]->getName() + " (" + board[i][j]->getAbbr() + ") [" + to_string(i) + "," + to_string(j) + "] attacked Homeowner. Homeowner lost " + to_string(board[i][j]->getDamage()) + " HP.");
					}
					else {
						if (dynamic_cast<Plant*>(board[i][j-1])) {
							// attack plant
							board[i][j-1]->setHP(board[i][j-1]->getHP() - board[i][j]->getDamage());
							eventMsg.push_back(board[i][j]->getName() + " (" + board[i][j]->getAbbr() + ") [" + to_string(i) + "," + to_string(j) + "] attacked " + board[i][j - 1]->getName() + " (" + board[i][j - 1]->getAbbr() + ") [" + to_string(i) + "," + to_string(j - 1) + "]. " + board[i][j - 1]->getName() + " (" + board[i][j - 1]->getAbbr() + ") [" + to_string(i) + "," + to_string(j - 1) + "] lost " + to_string(board[i][j]->getDamage()) + " HP.");
						}

						// move
						int moveby = 0;
						for (int k = 1; k <= zombiePtr->getSpeed(); k++) {
							if (j - k < 0)
								// out of battlefield
								break;
							else if (board[i][j - k])
								// blocked by creature
								break;
							else
								moveby = k;
						}
						if (moveby > 0) {
							board[i][j - moveby] = board[i][j];
							eventMsg.push_back(board[i][j]->getName() + " (" + board[i][j]->getAbbr() + ") [" + to_string(i) + "," + to_string(j) + "] moved to [" + to_string(i) + "," + to_string(j - moveby) + "].");
							board[i][j] = NULL;
						}
					}
				}
				else {
					// Plant can attack zombie
					for (int k = 1; k <= board[i][j]->getAtkRange(); k++) {
						if (j + k > 9)
							// out of battlefield
							break;
						else if (board[i][j+k]) {
							if (dynamic_cast<Zombie*>(board[i][j+k])) {
								// attack zombie
								board[i][j + k]->setHP(board[i][j+k]->getHP()-board[i][j]->getDamage());
								eventMsg.push_back(board[i][j]->getName() + " (" + board[i][j]->getAbbr() + ") [" + to_string(i) + "," + to_string(j) + "] attacked " + board[i][j+k]->getName() + " (" + board[i][j+k]->getAbbr() + ") [" + to_string(i) + "," + to_string(j+k) + "]. " + board[i][j+k]->getName() + " (" + board[i][j+k]->getAbbr() + ") [" + to_string(i) + "," + to_string(j+k) + "] lost " + to_string(board[i][j]->getDamage()) + " HP.");
								break;
							}
						}
					}
					// Sunflower can generate additional sun
					if (dynamic_cast<Sunflower*>(board[i][j])){
						homeowner->setSun(homeowner->getSun() + 1);
						eventMsg.push_back(board[i][j]->getName() + " (" + board[i][j]->getAbbr() + ") [" + to_string(i) + "," + to_string(j) + "] generated an additional sun for Homeowner.");
					}
				}
			}
		}
	}

	printBoard();

	// print event messages
	printEventMsg();

	pressToContinue();

	// check if any creature is killed (HP <= 0)
	eventMsg.clear();
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 10; j++) {
			if (board[i][j]) {
				if (board[i][j]->getHP() <= 0) {
					eventMsg.push_back(board[i][j]->getName() + " (" + board[i][j]->getAbbr() + ") [" + to_string(i) + "," + to_string(j) + "] is killed.");
					delete board[i][j];
					board[i][j] = NULL;
				}
			}
		}
	}
	if (!eventMsg.empty()) {
		system("cls");
		cout << "End of Round " << round << endl;
		printBoard();
		printEventMsg();
		pressToContinue();
	}

	// check whether game is end
	if (homeowner->getHP() <= 0 || round == roundMax)
		gameEnd = true;
	else
		round++;

}

void Game::endGame() {
	system("cls");
	cout << "End of Game" << endl;
	printBoard();
	// check who win
	if (homeowner->getHP() <= 0) {
		cout << "Homeowner is killed!" << endl;
		cout << "Zombie Army wins!" << endl;
		cout << zombiearmy->getName() << " wins!" << endl;
	}
	else {
		cout << "Homeowner survived!" << endl;
		cout << "Homeowner wins!" << endl;
		cout << homeowner->getName() << " wins!" << endl;
	}

	// deallocate memory
	delete homeowner;
	delete zombiearmy;
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 10; j++)
			delete board[i][j];

	pressToContinue();
	// ask play again
	system("cls");
	cout << "Play again?" << endl;
	cout << "1. Yes" << endl;
	cout << "2. No" << endl;
	char playagain;
	do {
		playagain = _getch();
	} while (!(playagain == '1' || playagain == '2'));
	if (playagain == '1') {
		Game game;
		game.startGame();
	}
	else {
		system("cls");
		exit(0);
	}
}

void Game::collectOccupied() {
	// collect occupied positions
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 10; j++)
			if (board[i][j])
				occupiedList.push_back(make_pair(i, j));
}

void Game::clearOccupied() {
	// clear occupied positions
	occupiedList.clear();
}

void Game::growPlants(char p, pair <int, int> pos) {
	system("cls");
	switch (p) {
	case '1': board[pos.first][pos.second] = new Peashooter(); break;
	case '2': board[pos.first][pos.second] = new BonkChoy(); break;
	case '3': board[pos.first][pos.second] = new Threepeater(); break;
	case '4': board[pos.first][pos.second] = new Wallnut(); break;
	case '5': board[pos.first][pos.second] = new Sunflower(); break;
	}
	cout << "Round " << round << endl;
	cout << "Homeowner Turn" << endl;
	printBoard();
	for (vector <plantCost>::iterator it = plantCostList.begin(); it != plantCostList.end(); it++) {
		if (it->id == p) {
			cout << "Homeowner used " << it->cost << " sun to grow " << it->name << " [" << pos.first << "," << pos.second << "]." << endl;
			break;
		}
	}
	pressToContinue();
}

void Game::produceZombies(char p, pair <int, int> pos) {
	system("cls");
	switch (p) {
	case '1': board[pos.first][pos.second] = new BasicZombie(); break;
	case '2': board[pos.first][pos.second] = new Buckethead(); break;
	case '3': board[pos.first][pos.second] = new Football(); break;
	case '4': board[pos.first][pos.second] = new Conehead(); break;
	}
	cout << "Round " << round << endl;
	cout << "Zombie Army Turn" << endl;
	printBoard();
	for (vector <zombieCost>::iterator it = zombieCostList.begin(); it != zombieCostList.end(); it++) {
		if (it->id == p) {
			cout << "Zombie Army used " << it->cost << " coin to produce " << it->name << " [" << pos.first << "," << pos.second << "]." << endl;
			break;
		}
	}
	pressToContinue();
}

void Game::pressToContinue() const {
	cout << endl;
	cout << "Press any key to continue...";
	_getch();
}

void Game::printEventMsg() {
	for (vector <string>::iterator it = eventMsg.begin(); it != eventMsg.end(); it++)
		cout << *it << endl;
}
