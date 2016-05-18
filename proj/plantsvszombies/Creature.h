#ifndef CREATURE_H
#define CREATURE_H

#include <string>
using namespace std;

class Creature {
public:
	virtual ~Creature();
	string getName() const;
	string getAbbr() const;
	int getDamage() const;
	int getHP() const;
	int getAtkRange() const;
	void setHP(int hp);

protected:
	string name;
	string abbr;
	int damage;
	int HP;
	int atkRange;
};
#endif // CREATURE_H
