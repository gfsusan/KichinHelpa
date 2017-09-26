#include "Recipe.h"

int Recipe::idCount = 0;


// 레시피.h를 Greeter에 include 안하기 위해서 
Recipe Recipe::readFromInput() {

	// Recipe()는 레시피의 이름, ID, 재료리스트, 요리법을 묻는다.
	int choice;

	string name;
	vector<Ingredient> ingredients;
	vector<string> cookingAlg;


	cout << "새로운 레시피를 추가합니다. " << endl << endl;

	// 레시피 이름
	cout << "이름: ";
	cin.ignore(256,'\n');
	getline(cin, name);
	cout << "ID: " << idCount + 1;
	
	// 레시피 재료 추가
	cout << endl<< endl << "재료를 추가합니다. ";
	cout << "재료를 입력하세요. ex) 당근 1 개";

	while (1) {

		Ingredient tempI = Ingredient::readFromInput();
		ingredients.push_back(tempI);

		cout << endl;
		cout << "1. 재료 추가\t2. 요리법 작성\tYour Choice: ";

		cin >> choice;

		if (choice == 1)
			continue;
		else if (choice == 2)
			break;
		// 윗부분 이거는 나중에 키 입력 받아서 엔터치는걸로 바꾸면 예외처리 할필요없을듯
	}

	cout << "Ingredient List 작성 완료" << endl << endl;		// test line

	system("cls");
	// 요리법 입력
	cout << "요리법을 순서대로 입력하세요. " << endl;
	while (1) {
		string tempAlg;

		cout << endl;

		// 요리법 묻기
		cin.ignore(256, '\n');
		getline(cin, tempAlg);			
		cookingAlg.push_back(tempAlg);

		cout << endl << "1. 요리법 추가\t2. Finish\tYour Choice: ";

		cin >> choice;

		if (choice == 1)
			continue;
		else if (choice == 2)
			break;
		// 윗부분 이거는 나중에 키 입력 받아서 엔터치는걸로 바꾸면 예외처리 할필요없을듯
	}

	//Recipe(name, ingredients, cookingAlg).printRecipe();

	return Recipe(name, ingredients, cookingAlg);
}

Recipe::Recipe(string nameR, vector<Ingredient> ingredients, vector<string> cookingAlg)
{
	this->nameR = nameR;
	this->idR = ++Recipe::idCount;
	this->ingredients = ingredients;
	this->cookingAlg = cookingAlg;
	//this->annotation = annotation;
	this->used = false;
}

Recipe::Recipe(string parsingLine) {
	vector<string> tokens;

	Tokenize(parsingLine, tokens, "/");//파싱한게 tokens안에 들어감.

									   //레시피이름
	this->nameR = tokens.at(0);
	//레시피 아이디
	this->idR = atoi(tokens.at(1).c_str());

	//레시피 재료
	vector<string> ingredients;//재료들
	vector<string> ingreEx;//재료 이름, 수량, 단위
	Tokenize(tokens.at(2), ingredients, "$");
	for (int i = 0; i < ingredients.size(); i++) {
		ingreEx.clear();
		Tokenize(ingredients.at(i), ingreEx, "@");
		this->ingredients.push_back(Ingredient (ingreEx.at(0), atoi(ingreEx.at(1).c_str()), ingreEx.at(2)));
	}

	//요리법
	vector<string> cooking;
	Tokenize(tokens.at(3), cooking, "@");
	for (int i = 0; i < cooking.size(); i++) {
		cookingAlg.push_back(cooking.at(i));
	}

}

Recipe::~Recipe() {
}

// 
void Recipe::printRecipe() {

	if (nameR.compare("")==0)
		return;
	else {
		cout << "Recipe Name : " << nameR << endl << endl;
		cout << "Ingredients :\n";
		printIngredients();

		cout << "How to cook :\n";
		for (int i = 0; i < cookingAlg.size(); i++) {
			cout << i + 1 << ". " << cookingAlg.at(i) << "\n";
		}
		cout << endl;
	}
}

void Recipe::printRecipe(Recipe* temp) {

	if (temp == NULL)
		return;
	else {
		cout << "Recipe Name : " << nameR << endl;
		cout << "Ingredients :\n";
		printIngredients();

		cout << "How to cook :\n";
		for (int i = 0; i < cookingAlg.size(); i++) {
			cout << i + 1 << ". " << cookingAlg.at(i) << "\n";
		}
		cout << endl;
	}
}


// 재료 이름, 수량, 단위 출력
void Recipe::printIngredients() {
	for (int i = 0; i<ingredients.size(); i++) {
		cout << ingredients.at(i).getNameI() << " " << ingredients.at(i).getNumI() << " " << ingredients.at(i).getUnitI() << "\n";
	}
	cout << endl;
}

// 재료 이름, 수량*사람수, 단위 출력 
void Recipe::printIngredients(int num) {
	for (int i = 0; i < ingredients.size(); i++) {
		cout << ingredients.at(i).getNameI() << ingredients.at(i).getNumI() * num << ingredients.at(i).getUnitI();
	}
}

// 재료 이름 출력
void Recipe::printIngre() {
	for (int i = 0; i<ingredients.size(); i++) {
		cout << i + 1 << ") " << ingredients.at(i).getNameI() << endl;
	}
	cout << endl;
}

//edit 화면전환, 종료 만들기 -반복 접근 없이 여러 개(여러 줄) 수정할 수 있도록, 뒤로 가기 전까지 화면이 끝나면안됨
void Recipe::editRecipe()
{
	int num;
	//printRecipe();
	while (1) {
		system("cls");
		printRecipe();
		cout << "What would you like to edit?\n";
		cout << "1. Name\t 2. Ingredients\t 3. How to cook 4. Back\t\tYour Choice: " ;
		cin >> num;
		if (num == 1) {
			editName();
		}
		else if (num == 2) {
			editIngredients();
			//printIngredients();
		}
		else if (num == 3) {
			editCookingAlg();
		}
		else if (num == 4) { // go back to where?? greeter
			//go to greeter greeter 객체 부르기

			break;
		}
		else
			cout << "Enter a valid number.";

	}
}

bool Recipe::isUsed() {
	return used;
}

void Recipe::setUsed() {
	this->used = true;
}

void Recipe::setUnused() {
	this->used = false;
}

void Recipe::editName()
{
	string newName;
	
	cout << "Enter a new name : ";
	cin.ignore(256, '\n');
	getline(cin, newName);
	cout << "The name changed from  \"" << nameR << "\" to \"" << newName << "\"\n";
	nameR = newName;
}

// 레시피 수정 시 edit ingredients(add, delete, edit)
void Recipe::editIngredients()
{
	int ingredientNum;
	int selectNum;

	printIngre();
	cout << "1. add\t\t2. delete\t3. edit\t\tYour Choice: ";
	cin >> selectNum;

	if (selectNum == 1) {
		addIngredient();
	}

	//db에 저장된 ingredient리스트 사용하여 추가할지, 새로 추가할지
	else if (selectNum == 2 || selectNum == 3) {
		cout << "Select the number you want to delete/edit : ";
		cin >> ingredientNum;

		if (selectNum == 2) {
			ingredients.erase(ingredients.begin() + ingredientNum - 1);
		}
		else if (selectNum == 3) {
			ingredients.erase(ingredients.begin() + ingredientNum - 1);
			addIngredient(); // add를 마지막에 할 지 아니면 수정되는 위치에 할 지 결정 *****

			//cin >> ingredients.insert(ingredientNum,);
			//수정 시 새로운 객체를 삽입. 새로운 객체를 리턴받아야해
		}
	}
	else {
		cout << "Enter a valid number";
	}
}

void Recipe::editCookingAlg() {
	int selectNum;
	int algNum;
	string newAlg;

	cout << "1. add\t2. delete\t3. edit\n";
	cin >> selectNum;
	cout << "Select the number you want to add/delete/edit : ";
	cin >> algNum;
	if (selectNum == 1) {
		cout << "추가할 내용을 입력해 주세요.\n";
		cin.ignore(256, '\n');
		getline(cin, newAlg);
		if (algNum - 1 < cookingAlg.size()) {
			cookingAlg.insert(cookingAlg.begin() + algNum - 1, newAlg);
		}
		else if (algNum - 1 == cookingAlg.size()) {
			cookingAlg.push_back(newAlg);
		}
		else
			cout << "숫자가 없습니다.\n";

	}
	//db에 저장된 ingredient리스트 사용하여 추가할지, 새로 추가할지
	else if (selectNum == 2) {
		cookingAlg.erase(cookingAlg.begin() + algNum - 1);
	}
	else if (selectNum == 3) {
		cout << "수정할 내용을 입력해 주세요.\n";
		cin.ignore(256, '\n');
		getline(cin, newAlg);
		cookingAlg.insert(cookingAlg.begin() + algNum - 1, newAlg);
		cookingAlg.erase(cookingAlg.begin() + algNum);
	}
	else {
		cout << "Enter a valid number";
	}
}


bool Recipe::hasIngredient(string ingredientName) {
	/*
	for (int i = 0; i < ingredients.size(); i++) {
		if (ingredients.at(i).getNameI().compare(S) == 0) {
			return getNameR();
		}
	}
	*/
	
	for (auto iter = ingredients.begin(); iter != ingredients.end(); iter++) {
		if (iter->getNameI().compare(ingredientName) == 0)
			return true;
	}
	
	return false;
}


void Recipe::addIngredient() {
	ingredients.push_back(Ingredient::readFromInput());

}


vector<Ingredient> Recipe::getIngredient() {
	return ingredients;
}

void Recipe::setIdCount(int n) {
	idCount = n;
}

string Recipe::getNameR() {
	return nameR;
}

int Recipe::getId(){
	return this->idR;
}

vector<string> Recipe::getCookingAlg() {
	return cookingAlg;
}

void Recipe::Tokenize(const string& str, vector<string>& tokens, const string& delimiters) {
	// 맨 첫 글자가 구분자인 경우 무시
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// 구분자가 아닌 첫 글자를 찾는다
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos)
	{
		// token을 찾았으니 vector에 추가한다
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		// 구분자를 뛰어넘는다.
		lastPos = str.find_first_not_of(delimiters, pos);
		// 다음 구분자가 아닌 글자를 찾는다
		pos = str.find_first_of(delimiters, lastPos);
	}
}
