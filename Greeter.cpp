#include "Greeter.h"
#include "RecipeDB.h"
#include "PlanManager.h"

enum {
	PROGRAM_END = 0,
	SEARCH_INGREDIENT,
	BROWSE_RECIPE,
	INSERT_RECIPE,
	EDIT_RECIPE,
	REVIEW_PLAN,
	CREATE_PLAN
};

Greeter::Greeter() {
	// �����ͺ��̽� ��ü ����
	db = RecipeDB::Instance();
	//pm = PlanManager::instance();
	choice();
}

Greeter::~Greeter() {

}

void Greeter::choice() {
	int num = 1;
	while (1) {

		system("cls");

		db->printDB();
	//pm->planlist(2017, 9, 25, 5);

		cout << "Hello! This is your IIKH (Interactive Intelligent Kitchen Helper).\n";

		cout << "\nYou can choose among 5 options :\n";
		cout << PROGRAM_END << ". (����) End program.\n";
		cout << SEARCH_INGREDIENT << ". (��� �˻�)\n";
		cout << BROWSE_RECIPE << ". (������ �˻�) Browse the database of existing recipes\n";
		//, but without reference to any particular meal plan.\n";
		cout << INSERT_RECIPE << ". (������ �߰�) Add a new recipe to the database.\n";
		cout << EDIT_RECIPE << ". (������ ����) Edit or annotate an existing recipe.\n";
		cout << REVIEW_PLAN << ". (�÷� �˻�) Review an existing plan for several meals.\n";
		cout << CREATE_PLAN << ". (�÷� �߰�) Create a new plan of meals.\n\n";


		cout << "Choose a number : ";
		cin >> num;

		if (num == SEARCH_INGREDIENT) { // recipe ��ü ��� �� �˻� �ϱ�
			system("cls");
			db->searchIngredients();
			system("pause");
		}
		else if (num == BROWSE_RECIPE) {
			
			system("cls");
			Recipe* temp;
			temp = db->browseRecipe();
			if (temp != NULL)
				temp->printRecipe();
			system("pause");
		}
		else if (num == INSERT_RECIPE) { // �ٷ� add ����
			system("cls");
			db->insertRecipe(Recipe::readFromInput());
			// insertRecipe(���ڷ� Recipe�� �޴� ���� �ڿ�������)
			// �׷��� �Է��� �޾� �Է��� ���� ���ο� �����Ǹ� �����Ͽ� �����ϴ� �Լ� ����
			// class���� dependency ���� 
			system("pause");
		}
		else if (num == EDIT_RECIPE) { // recipe ��ü ��� �� ������ �� ��ȣ �ޱ�
			system("cls");
			db->editRecipeList();
			system("puase");
		}
		else if (num == REVIEW_PLAN) { // ���� ��¥�� �´� �޷� ��� �� ��¥ �˻�
			pm->browsePlan();
		}
		else if (num == CREATE_PLAN) { // ���� ��¥�� �´� �޷� ��� �� ��¥ �˻�
			pm->insertPlan(Date::readFromInput());
		}
		else if (num == PROGRAM_END) {
			db->writeToFile();
			break;
		}
		else {
			cout << "You wrote the wrong number.\n";
		}
	}
	cout << "\nIIKH is ended. Thank you.\n";
}

