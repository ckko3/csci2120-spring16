#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <string>
#include "Creature.h"
using namespace std;

class Zombie : public Creature {
public:
	Zombie(string name, string abbr, int damage, int HP, int atkRange, int speed);
	int getSpeed() const;
private:
	int speed;
};
#endif // ZOMBIE_H
