#ifndef ZOMBIEARMY_H
#define ZOMBIEARMY_H

#include <string>
#include <vector>
#include "Player.h"
using namespace std;

class ZombieArmy : public Player {
public:
  ZombieArmy(string name, int type);
  int getCoin() const;
  void setCoin(int c);
  char getMove(vector <pair <int, int>>& pos);
  pair <int,int> getPosition(char p, vector <pair <int, int>>& pos);
  void printZombies();
private:
  int coin;
  struct zombie {
	  char id;
	  string name;
	  int damage;	// none: 0, weak: 1, normal: 3, heavy: 5
	  int HP;	// low: 5, normal: 7, high: 9
	  int atkRange;	// none: 0, short: 1, long: 5
	  int cost;	// low: 1, normal: 3, high: 5
	  int speed; // slow: 1, normal: 3, fast: 5
  };
  vector <zombie> zombieList;
};
#endif // ZOMBIEARMY_H
