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

	Recipe* browseRecipe();	// 안에서 id입력받아 searchRecipe(id)로 보냄
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

	// 파일입출력
	ofstream ofRecipeDB;
	ifstream ifRecipeDB;

	// 파일을 읽어서 요기에 집어넣기
	vector<Recipe> recipeDB;

	int id = 0;
};