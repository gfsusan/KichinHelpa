#pragma once

#include "Ingredient.h"
#include "Recipe.h"

#include <vector>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class RecipeDB {
public:
	static RecipeDB* Instance();
	~RecipeDB();

	void insertRecipe(Recipe);
	void deleteRecipe(int);
	void editRecipeList();

	Recipe* browseRecipe();	// �ȿ��� id�Է¹޾� searchRecipe(id)�� ����
	Recipe* searchRecipe(int searchId);
	void searchIngredients();

	void printDB();
	void printSearchedDB(vector<Recipe> recipeList);
	string printRecipe(int);

	int getRecipeDBsize();
	vector<Recipe> getrecipeDB();

	void RecipeDB::writeToFile();

private:
	static RecipeDB* ptrDB;
	RecipeDB();

	void readFromFile();

	// ���������
	ofstream ofRecipeDB;
	ifstream ifRecipeDB;

	// ������ �о ��⿡ ����ֱ�
	vector<Recipe> recipeDB;

	int id = 0;
};