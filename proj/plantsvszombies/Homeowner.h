#ifndef HOMEOWNER_H
#define HOMEOWNER_H

#include <string>
#include <vector>
#include <utility>
#include "Player.h"
using namespace std;

class Homeowner : public Player {
public:
  Homeowner(string name, int type);
  int getHP() const;
  int getSun() const;
  void setHP(int hp);
  void setSun(int s);
  char getMove(vector <pair <int, int>>& pos);
  pair <int, int> getPosition(char p, vector <pair <int, int>>& pos);
  void printPlants();
private:
  int HP;
  int sun;
  struct plant {
	  char id;
	  string name;
	  int damage;	// none: 0, weak: 1, normal: 3, heavy: 5
	  int HP;	// low: 5, normal: 7, high: 9
	  int atkRange;	// none: 0, short: 1, long: 5
	  int cost;	// low: 1, normal: 3, high: 5
  };
  vector <plant> plantList;
};
#endif // HOMEOWNER_H
