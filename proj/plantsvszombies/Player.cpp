#include <iostream>
#include <conio.h>
#include "Player.h"
using namespace std;

// constuctor
Player::Player(string name, int type) : playerName(name), playerType(type) {
}

string Player::getName() const {
  return playerName;
}

int Player::getType() const {
  return playerType;
}

void Player::pressToContinue() const {
	cout << endl;
	cout << "Press any key to continue...";
	_getch();
}
