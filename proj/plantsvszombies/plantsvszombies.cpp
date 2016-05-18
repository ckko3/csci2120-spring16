#include <iostream>
#include <cstdlib>	// srand
#include <ctime>	// time
#include "Game.h"
using namespace std;

int main() {
  srand((unsigned int)time(0)); // initialize the random number sequence, execute once only in the program
  Game game;
  game.startGame();
  return 0;
}
