#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Player {
public:
  Player(string name, int type);
  string getName() const;
  int getType() const;
  void pressToContinue() const;
private:
  string playerName;
  int playerType;
};
#endif // PLAYER_H
