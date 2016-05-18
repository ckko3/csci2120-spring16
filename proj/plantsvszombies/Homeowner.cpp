#include <iostream>
#include <conio.h>	// _getch
#include <vector>
#include <algorithm>	// random_shuffle
#include "Homeowner.h"
using namespace std;

// constuctor
Homeowner::Homeowner(string name, int type) : Player(name, type) {
  HP = 10;
  sun = 10;
  plantList.push_back({ '1', "Peashooter (PS)", 3, 5, 5, 1 });	// normal, low, long, low
  plantList.push_back({ '2', "Bonk Choy (BC)", 5, 7, 1, 3 });	// heavy, normal, short, normal
  plantList.push_back({ '3', "Treepeater (TP)", 5, 5, 5, 5 });	// heavy, low, long, high
  plantList.push_back({ '4', "Wall-nut (WN)", 0, 9, 0, 3 });	// none, high, none, normal
  plantList.push_back({ '5', "Sunflower (SF)", 0, 5, 0, 1 });	// none, low, none, low, generate sun
}

int Homeowner::getHP() const {
  return HP;
}

int Homeowner::getSun() const {
  return sun;
}

void Homeowner::setSun(int s) {
	sun = s;
}

void Homeowner::setHP(int hp) {
	HP = hp;
}

char Homeowner::getMove(vector <pair <int, int>>& pos) {
	// check if all grids except rightmost occupied
	int occupiedCount = 0;
	for (vector <pair <int, int>>::iterator it = pos.begin(); it != pos.end(); it++)
		if (it->second != 9)
			occupiedCount++;
	if (occupiedCount == 54) {
		cout << "All available grids occupied! No more plants can be produced." << endl;
		pressToContinue();
		return '6';
	}

	char p;	// return value
	if (getType() == 1) {
		// human player
		bool validMove;

		do {
			validMove = true;
			cout << "Which plant to grow?" << endl;
			printPlants();
			cout << "6. Do not grow plants" << endl;

			// ignore invalid input
			do {
				p = _getch();
			} while (!(p == '1' || p == '2' || p == '3' || p == '4' || p == '5' || p == '6'));

			if (p != '6') {
				// check whether enough sun
				for (vector <plant>::iterator it = plantList.begin(); it != plantList.end(); it++) {
					if (it->id == p) {
						if (getSun() < it->cost) {
							cout << "Invalid move! Not enough sun to grow " << it->name << "." << endl;
							validMove = false;
						}
						else {
							setSun(getSun() - it->cost);
						}
						break;
					}
				}
			}
		} while (!validMove);
	}
	else {
		// computer player
		// randomly grow plants as much as possible
		vector <char> availablePlant;
		for (vector <plant>::iterator it = plantList.begin(); it != plantList.end(); it++)
			if (getSun() >= it->cost)
				availablePlant.push_back(it->id);
		if (availablePlant.empty())
			// not enough sun to grow any plants
			p = '6';
		else {
			random_shuffle(availablePlant.begin(), availablePlant.end());
			p = availablePlant.front();
			for (vector <plant>::iterator it = plantList.begin(); it != plantList.end(); it++) {
				if (it->id == p) {
					setSun(getSun() - it->cost);
					break;
				}
			}
		}
	}

	return p;

}

pair <int, int> Homeowner::getPosition(char p, vector <pair <int, int>>& pos) {
	int r, c;	// return value
	bool validPosition;

	if (getType() == 1) {
		// human player
		string plant;
		switch (p) {
		case '1': plant = "Peashooter (PS)"; break;
		case '2': plant = "Bonk Choy (BC)"; break;
		case '3': plant = "Treepeater (TP)"; break;
		case '4': plant = "Wall-nut (WN)"; break;
		case '5': plant = "Sunflower (SF)"; break;
		}

		do {
			validPosition = true;
			cout << "Which grid [0-5] [0-8] to plant " << plant << "?" << endl;

			if (!(cin >> r >> c) || r < 0 || r > 5 || c < 0 || c > 8) {
				cout << "Invalid position! The position must be [0-5] [0-8]." << endl;
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
		// grow plants at random position
		do {
			validPosition = true;
			r = rand() % 6;
			c = rand() % 9;
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

void Homeowner::printPlants() {
	for (vector <plant>::iterator it = plantList.begin(); it != plantList.end(); it++) {
		cout << it->id << ". " << it->name;
		printf("\t");
		cout << "(Damage: " << it->damage << ")";
		printf("\t");
		cout << "(HP: " << it->HP << ")";
		printf("\t");
		cout << "(Attack Range: " << it->atkRange << ")";
		printf("\t");
		cout << "(Cost: " << it->cost << ")";
		cout << endl;
	}
}

