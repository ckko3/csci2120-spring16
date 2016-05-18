#include <iostream>
#include <string>
#include "Plant.h"
using namespace std;

Plant::Plant(string name, string abbr, int damage, int HP, int atkRange) {
	this->name = name;
	this->abbr = abbr;
	this->damage = damage;
	this->HP = HP;
	this->atkRange = atkRange;
}
