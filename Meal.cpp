#include "Meal.h"
#include <random>
#include <ctime>
#include <cstdlib>

Meal::Meal() {

}

Meal::~Meal() {

}

void Meal::makeMealP(int num) {   // edit �� �� num �޾Ƽ� �� ��ġ�� �����ؼ� ����

	int id;
	recipeDB->printDB();

	while (1) {

		// id �Է¹ޱ�
		cin >> id;

		if (recipeDB->searchRecipe(id) != NULL) {
			recipeIDs.insert(recipeIDs.begin() + id - 1, id);
			recipeIDs.erase(recipeIDs.begin() + id);
		}
	}
}

void Meal::makeMealP() {   //�츮�� �����ؼ�

	int id;
	char choice;
	recipeDB->printDB();

	while (1) {
		cin >> id;

		if (recipeDB->searchRecipe(id) != NULL)
			recipeIDs.push_back(id);

		cout << "�� �߰��Ͻðڽ��ϱ�? (Y/N) " << endl;
		cin >> choice;
		if (choice == 'Y' || choice == 'y')
			continue;
		else if (choice == 'N' || choice == 'n')
			break;
		else
			cout << "Enter a valid number";
	}
}



void Meal::makeMealC() {   //��ǻ�Ͱ� ��������
	int num;
	int numRecipe;
	int temp;

	srand(time(NULL));
	numRecipe = recipeDB->getRecipeDBsize();

	cout << "How many foods do you want to cook?";
	cin >> num;

	for (int i = 0; i < num; i++)
	{
		temp = rand() % numRecipe;
		recipeIDs.push_back(temp);
	}

}

void Meal::editMeal() {

	int selectNum;
	int recipeId;

	printRecipeName(); // ���� ���� �ִ� ��
	recipeDB->printDB(); // ������ �߰��� ��
	while (1)
	{
		cout << "1. add\t2. delete\t3. edit\n 4. back";
		cin >> selectNum;

		if (selectNum == 1) {
			makeMealP();
		}

		//db�� ����� ingredient����Ʈ ����Ͽ� �߰�����, ���� �߰�����
		else if (selectNum == 2) {
			cout << "Select the number you want to delete : ";
			cin >> recipeId;
			recipeIDs.erase(recipeIDs.begin() + recipeId - 1);
		}
		else if (selectNum == 3) {
			cout << "Select the number you want to edit : ";
			cin >> recipeId;
			recipeIDs.erase(recipeIDs.begin() + recipeId - 1);
			makeMealP();
		}
		else if (selectNum == 4)
		{
			break;
		}

		else
			cout << "Enter a valid number";
	}
	//break�� ������ �� �ش� �ϴ� �� ȭ�� call
}
void Meal::printGroceryList(int people) {
	int num = recipeIDs.size();
	vector<Recipe> recipeDB = RecipeDB::Instance()->getrecipeDB();

	for (int i = 0; i < recipeIDs.size(); i++)
	{
		recipeDB.at(i).printIngredients(people);
	}

	//tempR = recipeDB.at(i).searchIngredient(searchIngredients);
}

void Meal::printRecipeName() {
	for (int i = 0; i < recipeIDs.size(); i++) {
		cout << recipeIDs.at(i) << ") " << recipeDB->printRecipe(recipeIDs.at(i)) << endl;
	}
	cout << endl;
}

void Meal::pushMealId(int mealid) {
	recipeIDs.push_back(mealid);
}

vector<int> Meal::getIDList() {
	return recipeIDs;

}

int Meal::getRecipeIDsize() {
	return recipeIDs.size();
}