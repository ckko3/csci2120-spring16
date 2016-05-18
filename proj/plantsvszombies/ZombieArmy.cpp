#include <iostream>
#include <vector>
#include <conio.h>	// _getch
#include <algorithm>	// random_shuffle
#include "ZombieArmy.h"
using namespace std;

// constuctor
ZombieArmy::ZombieArmy(string name, int type) : Player(name, type) {
	coin = 10;
	zombieList.push_back({ '1', "Basic Zombie (BZ)", 3, 7, 1, 1, 3 });	// normal, normal, short, low, normal
	zombieList.push_back({ '2', "Buckethead (BH)", 3, 9, 1, 5, 3 });	// normal, high, short, high, normal
	zombieList.push_back({ '3', "Football (FB)", 1, 9, 1, 5, 5 });	// weak, high, short, high, fast
	zombieList.push_back({ '4', "Conehead (CH)", 5, 7, 1, 3, 1 });	// heavy, normal, short, normal, slow
}

int ZombieArmy::getCoin() const {
	return coin;
}

void ZombieArmy::setCoin(int c) {
	coin = c;
}

char ZombieArmy::getMove(vector <pair <int, int>>& pos) {
	// check if all rightmost grids occupied
	int occupiedCount = 0;
	for (vector <pair <int, int>>::iterator it = pos.begin(); it != pos.end(); it++)
		if (it->second == 9)
			occupiedCount++;
	if (occupiedCount == 6) {
		cout << "All rightmost grids occupied! No more zombies can be produced." << endl;
		pressToContinue();
		return '5';
	}

	char p;	// return value
	if (getType() == 1) {
		// human player
		bool validMove;

		do {
			validMove = true;
			cout << "Which zombie to produce?" << endl;
			printZombies();
			cout << "5. Do not produce zombies" << endl;

			// ignore invalid input
			do {
				p = _getch();
			} while (!(p == '1' || p == '2' || p == '3' || p == '4' || p == '5'));

			if (p != '5') {
				// check whether enough coin
				for (vector <zombie>::iterator it = zombieList.begin(); it != zombieList.end(); it++) {
					if (it->id == p) {
						if (getCoin() < it->cost) {
							cout << "Invalid move! Not enough coin to produce " << it->name << "." << endl;
							validMove = false;
						}
						else {
							setCoin(getCoin() - it->cost);
						}
						break;
					}
				}
			}
		} while (!validMove);
	}
	else {
		// computer player
		// randomly produce zombies as much as possible
		vector <char> availableZombie;
		for (vector <zombie>::iterator it = zombieList.begin(); it != zombieList.end(); it++)
			if (getCoin() >= it->cost)
				availableZombie.push_back(it->id);
		if (availableZombie.empty())
			// not enough coin to produce any zombies
			p = '5';
		else {
			random_shuffle(availableZombie.begin(), availableZombie.end());
			p = availableZombie.front();
			for (vector <zombie>::iterator it = zombieList.begin(); it != zombieList.end(); it++) {
				if (it->id == p) {
					setCoin(getCoin() - it->cost);
					break;
				}
			}
		}
	}

	return p;

}

pair <int, int> ZombieArmy::getPosition(char p, vector <pair <int, int>>& pos) {
	int r;	int c = 9;	// return value
	bool validPosition;

	if (getType() == 1) {
		// human player
		string zombie;
		switch (p) {
		case '1': zombie = "Basic Zombie (BZ)"; break;
		case '2': zombie = "Buckethead (BH)"; break;
		case '3': zombie = "Football (FB)"; break;
		case '4': zombie = "Conehead (CH)"; break;
		}

		do {
			validPosition = true;
			cout << "Which row [0-5] to produce " << zombie << "?" << endl;
			
			if (!(cin >> r) || r < 0 || r > 5) {
				cout << "Invalid row! The row must be [0-5]." << endl;
				validPosition = false;
			}
			else {
				for (vector <pair <int, int>>::iterator it = pos.begin(); it != pos.end(); it++) {
					if (r == it->first && c == it->second) {
						cout << "Invalid position! [" << r << "," << c << "] is occupied." << endl;
						validPosition = false;
						break;
					}
				}
			}
			cin.clear();
			cin.ignore(10000, '\n');

		} while (!validPosition);
	}
	else {
		// computer player
		// produce zombies at random position
		do {
			validPosition = true;
			r = rand() % 6;
			for (vector <pair <int, int>>::iterator it = pos.begin(); it != pos.end(); it++) {
				if (r == it->first && c == it->second) {
					validPosition = false;
					break;
				}
			}

		} while (!validPosition);
	}

	return make_pair(r, c);

}

void ZombieArmy::printZombies() {
	for (vector <zombie>::iterator it = zombieList.begin(); it != zombieList.end(); it++) {
		cout << it->id << ". " << it->name;
		printf("\t");
		cout << "(Damage: " << it->damage << ")";
		printf("\t");
		cout << "(HP: " << it->HP << ")";
		printf("\t");
		cout << "(Attack Range: " << it->atkRange << ")";
		printf("\t");
		cout << "(Cost: " << it->cost << ")";
		printf("\t");
		cout << "(Speed: " << it->speed << ")";
		cout << endl;
	}
}
