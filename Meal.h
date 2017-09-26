#pragma once

#include "Recipe.h"
#include "RecipeDB.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Meal {
public:
	Meal();
	~Meal();

	void makeMealP();
	void makeMealP(int num);
	void makeMealC();
	void editMeal();

	void pushMealId(int mealid);

	void printGroceryList(int people);
	void printRecipeName();	// printRecipeList ?

	vector<int> Meal::getIDList();
	int Meal::getRecipeIDsize();

private:
	// 하나의 meal에 들어갈 recipe들 - Recipe객체를 갖고 올까 레시피 이름만 갖고 올까
	// meal에 필요한 grocery list
	//vector <Recipe> recipe4Meal;
	RecipeDB* recipeDB;
	vector<int> recipeIDs;

};