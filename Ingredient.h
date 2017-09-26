#pragma once

//#include "IIKH.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Ingredient {
public:
	Ingredient(string nameI, int numI, string unitI);
	~Ingredient();

	static Ingredient readFromInput();

	void editNameI(string);
	void editNumI(int);
	void editUnitI(string);

	string getNameI();
	int getNumI();
	string getUnitI();


private:
	string nameI;
	int numI;
	string unitI;
};
