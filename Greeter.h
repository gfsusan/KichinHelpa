#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "RecipeDB.h"
#include "PlanManager.h"

using namespace std;

//¿Ï¼º
class Greeter {
public:
	Greeter();
	~Greeter();

	void choice();

private:
	RecipeDB *db;
	PlanManager *pm;
	// RecipeDB recipeDB;
	// PlanManager planM;
};

