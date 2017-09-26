#include "RecipeDB.h"
#include "Recipe.h"
#include "Meal.h"

#include <cstdlib>
#include <fstream>

RecipeDB* RecipeDB::ptrDB = NULL;

// singleton 
RecipeDB* RecipeDB::Instance() {
	if (ptrDB == NULL)
		ptrDB = new RecipeDB();

	return ptrDB;
}

RecipeDB::RecipeDB() {
	recipeDB.clear();
	// ������ �о� ��Ʈ���� ������ ��ü�� �ٲپ��ִ°�  
	readFromFile();
	Recipe::setIdCount(recipeDB.rbegin()->getId());
}

RecipeDB :: ~RecipeDB() {
	writeToFile();
}

void RecipeDB::insertRecipe(Recipe recipe) {

	recipeDB.push_back(recipe);
	cout << "������ �߰� �Ϸ�." << endl;
}


void RecipeDB::deleteRecipe(int editRecipeId) {

	// erase the removeRecipeId'th element
	recipeDB.erase(recipeDB.begin() + editRecipeId - 1);
	cout << "Recipe ���� ����.";
}  //recipe���� �� �������� id�� ���� 


Recipe* RecipeDB::browseRecipe() {
	int searchId;

	system("cls");
	printDB(); // ������ �̸� ���
	if (recipeDB.empty() == false) {
		cout << "�˻��� ������ ��ȣ�� �Է��ϼ���: ";
		cin >> searchId;
		return searchRecipe(searchId);
	}
	else {

		return NULL;
	}
}

Recipe* RecipeDB::searchRecipe(int searchId) {

	// for-each ������, iter�� ������
	// recipeDB�� ��� �ִ� ��� Recipe check
	for (auto iter = recipeDB.begin(); iter != recipeDB.end(); iter++) {
		if (iter->getId() == searchId) { // id ������ ����
			return  &*iter;
		}
	}

	cout << "ID : " << searchId << "�� �����ǰ� �������� �ʽ��ϴ�." << endl;
	system("PAUSE");

	return NULL;
}


void RecipeDB::searchIngredients() {

	string name;
	vector<Recipe> tempList;

	system("cls");

	printDB();
	if (recipeDB.empty() == false) {
		cout << "�˻��� ��Ḧ �Է��ϼ��� : ";
		cin >> name;

		for (auto iter = recipeDB.begin(); iter != recipeDB.end(); iter++) {
			if (iter->hasIngredient(name) == true) {
				tempList.push_back(*iter);
			}
		}
		if (tempList.empty() == true) {
			cout << name << "��/�� �� ��ᰡ �����ϴ�.\n";
		}
		else
			printSearchedDB(tempList);
	}
}

void RecipeDB::editRecipeList() {

	int choice;
	int editRecipeId;
	printDB();
	cout << "������ ������ ��ȣ�� �Է��ϼ��� : ";
	cin >> editRecipeId;

	cout << "1. edit\t\t2.delete\tYour Choice: ";
	cin >> choice;

	system("cls");

	if (choice == 1)
		recipeDB.at(editRecipeId - 1).editRecipe();
	else if (choice == 2)
		this->deleteRecipe(editRecipeId);
}

void RecipeDB::printDB() {

	if (recipeDB.empty() == false) {
		cout << "\nid\tname\n";
		for (auto iter = recipeDB.begin(); iter != recipeDB.end(); iter++)   // ������ size Ÿ������ i�� �����Ѵ� (unsigned int) 
			cout << iter->getId() << ")\t" << iter->getNameR() << endl;
	}
	else
		cout << "����� �����ǰ� �����ϴ�." << endl;
	cout << endl << endl;
}

void RecipeDB::printSearchedDB(vector<Recipe> recipeList) {
	cout << "\nid\tname\n";
	if (!recipeList.empty())
		for (int i = 0; i < recipeList.size(); i++)   // ������ size Ÿ������ i�� �����Ѵ� (unsigned int) 
			cout << recipeList.at(i).getId() << ")\t" << recipeList.at(i).getNameR() << endl;
	else
		cout << "�����ǰ� �����ϴ�. " << endl;
	cout << endl << endl;
}

string RecipeDB::printRecipe(int num) {
	return recipeDB.at(num - 1).getNameR();
}

int RecipeDB::getRecipeDBsize() {
	return recipeDB.size();
}

vector<Recipe> RecipeDB::getrecipeDB() {
	return recipeDB;
}

void RecipeDB::readFromFile() {
	ifstream inFile("RecipeDB.txt", ios::in);
	if (inFile.is_open()) {
		string line;

		while (getline(inFile, line)) {
			this->recipeDB.push_back(Recipe(line));
		}

		inFile.close();

	}
	else cout << "Unable to open Recipefile";
}

void RecipeDB::writeToFile() {
	ofstream saving;
	saving.open("RecipeDB.txt", ios::out | ios::trunc);

	// name, id
	for (int i = 0; i < recipeDB.size(); i++) {
		saving << recipeDB.at(i).getNameR() << "/"
			<< recipeDB.at(i).getId() << "/";

		// ���
		for (int j = 0; j < recipeDB.at(i).getIngredient().size(); j++) {//������
			saving << recipeDB.at(i).getIngredient().at(j).getNameI() << "@"
				<< recipeDB.at(i).getIngredient().at(j).getNumI() << "@"
				<< recipeDB.at(i).getIngredient().at(j).getUnitI();
			if (j < recipeDB.at(i).getIngredient().size() - 1) {
				saving << "$";
			}
		}
		saving << "/";

		// �丮��
		for (int j = 0; j < recipeDB.at(i).getCookingAlg().size(); j++){
			saving << recipeDB.at(i).getCookingAlg().at(j);
			if (j < recipeDB.at(i).getCookingAlg().size() - 1) {
				saving << "@";
			}
		}
		saving << endl;
	}

	saving.close();
}