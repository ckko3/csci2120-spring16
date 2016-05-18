#include <iostream>
#include <string>
#include "Creature.h"
using namespace std;

Creature::~Creature() {
}

string Creature::getName() const {
	return name;
}
string Creature::getAbbr() const {
	return abbr;
}
int Creature::getHP() const {
	return HP;
}
int Creature::getDamage() const{
	return damage;
}
int Creature::getAtkRange() const{
	return atkRange;
}
void Creature::setHP(int hp) {
	HP = hp;
}