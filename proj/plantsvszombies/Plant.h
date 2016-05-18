#ifndef PLANT_H
#define PLANT_H

#include <string>
#include "Creature.h"
using namespace std;

class Plant : public Creature {
public:
	Plant(string name, string abbr, int damage, int HP, int atkRange);
};
#endif // PLANT_H
