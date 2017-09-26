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
	// 파일을 읽어 스트링을 레시피 객체로 바꾸어주는것  
	readFromFile();
	Recipe::setIdCount(recipeDB.rbegin()->getId());
}

RecipeDB :: ~RecipeDB() {
	writeToFile();
}

void RecipeDB::insertRecipe(Recipe recipe) {

	recipeDB.push_back(recipe);
	cout << "레시피 추가 완료." << endl;
}


void RecipeDB::deleteRecipe(int editRecipeId) {

	// erase the removeRecipeId'th element
	recipeDB.erase(recipeDB.begin() + editRecipeId - 1);
	cout << "Recipe 삭제 성공.";
}  //recipe에서 각 레시피의 id로 제거 


Recipe* RecipeDB::browseRecipe() {
	int searchId;

	system("cls");
	printDB(); // 레시피 이름 출력
	if (recipeDB.empty() == false) {
		cout << "검색할 레시피 번호를 입력하세요: ";
		cin >> searchId;
		return searchRecipe(searchId);
	}
	else {

		return NULL;
	}
}

Recipe* RecipeDB::searchRecipe(int searchId) {

	// for-each 같은거, iter는 포인터
	// recipeDB에 들어 있는 모든 Recipe check
	for (auto iter = recipeDB.begin(); iter != recipeDB.end(); iter++) {
		if (iter->getId() == searchId) { // id 같으면 리턴
			return  &*iter;
		}
	}

	cout << "ID : " << searchId << "의 레시피가 존재하지 않습니다." << endl;
	system("PAUSE");

	return NULL;
}


void RecipeDB::searchIngredients() {

	string name;
	vector<Recipe> tempList;

	system("cls");

	printDB();
	if (recipeDB.empty() == false) {
		cout << "검색할 재료를 입력하세요 : ";
		cin >> name;

		for (auto iter = recipeDB.begin(); iter != recipeDB.end(); iter++) {
			if (iter->hasIngredient(name) == true) {
				tempList.push_back(*iter);
			}
		}
		if (tempList.empty() == true) {
			cout << name << "이/가 들어간 재료가 없습니다.\n";
		}
		else
			printSearchedDB(tempList);
	}
}

void RecipeDB::editRecipeList() {

	int choice;
	int editRecipeId;
	printDB();
	cout << "수정할 레시피 번호를 입력하세요 : ";
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
		for (auto iter = recipeDB.begin(); iter != recipeDB.end(); iter++)   // 벡터의 size 타입으로 i를 지정한다 (unsigned int) 
			cout << iter->getId() << ")\t" << iter->getNameR() << endl;
	}
	else
		cout << "저장된 레시피가 없습니다." << endl;
	cout << endl << endl;
}

void RecipeDB::printSearchedDB(vector<Recipe> recipeList) {
	cout << "\nid\tname\n";
	if (!recipeList.empty())
		for (int i = 0; i < recipeList.size(); i++)   // 벡터의 size 타입으로 i를 지정한다 (unsigned int) 
			cout << recipeList.at(i).getId() << ")\t" << recipeList.at(i).getNameR() << endl;
	else
		cout << "레시피가 없습니다. " << endl;
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

		// 재료
		for (int j = 0; j < recipeDB.at(i).getIngredient().size(); j++) {//재료대입
			saving << recipeDB.at(i).getIngredient().at(j).getNameI() << "@"
				<< recipeDB.at(i).getIngredient().at(j).getNumI() << "@"
				<< recipeDB.at(i).getIngredient().at(j).getUnitI();
			if (j < recipeDB.at(i).getIngredient().size() - 1) {
				saving << "$";
			}
		}
		saving << "/";

		// 요리법
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