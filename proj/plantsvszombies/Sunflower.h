#ifndef SUNFLOWER_H
#define SUNFLOWER_H

#include <string>
#include "Plant.h"
using namespace std;

class Sunflower : public Plant {
public:
	Sunflower();
	void generateSun();
};
#endif // SUNFLOWER_H
