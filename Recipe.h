#pragma once

#include "Ingredient.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Recipe {
public:
	Recipe(string nameR, vector<Ingredient> ingredients, vector<string> cookingAlg);
	Recipe(string parsingLine);
	~Recipe();

	static Recipe readFromInput();	// Input 

	void printRecipe();
	void printRecipe(Recipe* temp);
	void printIngredients(); // ���� ���� ����
	void printIngredients(int);
	void printIngre(); // ��� �̸���

	void editRecipe();

	bool hasIngredient(string ingredientName);
	void addIngredient(); // ���  vector�� �����ϴ�

	vector<Ingredient> getIngredient(); //��� �Ѱ��ִ�

	string getNameR();
	vector<string> getCookingAlg();

	static void setIdCount(int);

	int getId();
	bool isUsed();
	void setUsed();
	void setUnused();

private:
	string nameR;
	int idR;
	vector<Ingredient> ingredients;
	vector<string> cookingAlg;
	bool used;

	// string annotation;

	void editName();
	void editIngredients();
	void editCookingAlg();

	void Tokenize(const string& str, vector<string>& tokens, const string& delimiters);


	//void Tokenize()

	static int idCount;
};
