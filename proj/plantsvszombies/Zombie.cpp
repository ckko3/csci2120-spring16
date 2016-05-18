#include <iostream>
#include <string>
#include "Zombie.h"
using namespace std;

Zombie::Zombie(string name, string abbr, int damage, int HP, int atkRange, int speed) {
	this->name = name;
	this->abbr = abbr;
	this->damage = damage;
	this->HP = HP;
	this->atkRange = atkRange;
	this->speed = speed;
}

int Zombie::getSpeed() const {
	return speed;
}

