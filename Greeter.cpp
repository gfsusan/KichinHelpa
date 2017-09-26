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
	// 데이터베이스 객체 생성
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
		cout << PROGRAM_END << ". (종료) End program.\n";
		cout << SEARCH_INGREDIENT << ". (재료 검색)\n";
		cout << BROWSE_RECIPE << ". (레시피 검색) Browse the database of existing recipes\n";
		//, but without reference to any particular meal plan.\n";
		cout << INSERT_RECIPE << ". (레시피 추가) Add a new recipe to the database.\n";
		cout << EDIT_RECIPE << ". (레시피 수정) Edit or annotate an existing recipe.\n";
		cout << REVIEW_PLAN << ". (플랜 검색) Review an existing plan for several meals.\n";
		cout << CREATE_PLAN << ". (플랜 추가) Create a new plan of meals.\n\n";


		cout << "Choose a number : ";
		cin >> num;

		if (num == SEARCH_INGREDIENT) { // recipe 전체 출력 후 검색 하기
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
		else if (num == INSERT_RECIPE) { // 바로 add 시작
			system("cls");
			db->insertRecipe(Recipe::readFromInput());
			// insertRecipe(인자로 Recipe를 받는 것이 자연스럽다)
			// 그래서 입력을 받아 입력을 토대로 새로운 레시피를 생성하여 리턴하는 함수 만듦
			// class간의 dependency 줄임 
			system("pause");
		}
		else if (num == EDIT_RECIPE) { // recipe 전체 출력 후 수정할 것 번호 받기
			system("cls");
			db->editRecipeList();
			system("puase");
		}
		else if (num == REVIEW_PLAN) { // 오늘 날짜에 맞는 달력 출력 후 날짜 검색
			pm->browsePlan();
		}
		else if (num == CREATE_PLAN) { // 오늘 날짜에 맞는 달력 출력 후 날짜 검색
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

