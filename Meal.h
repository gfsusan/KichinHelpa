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
	// �ϳ��� meal�� �� recipe�� - Recipe��ü�� ���� �ñ� ������ �̸��� ���� �ñ�
	// meal�� �ʿ��� grocery list
	//vector <Recipe> recipe4Meal;
	RecipeDB* recipeDB;
	vector<int> recipeIDs;

};