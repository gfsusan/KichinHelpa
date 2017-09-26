#include "Recipe.h"

int Recipe::idCount = 0;


// ������.h�� Greeter�� include ���ϱ� ���ؼ� 
Recipe Recipe::readFromInput() {

	// Recipe()�� �������� �̸�, ID, ��Ḯ��Ʈ, �丮���� ���´�.
	int choice;

	string name;
	vector<Ingredient> ingredients;
	vector<string> cookingAlg;


	cout << "���ο� �����Ǹ� �߰��մϴ�. " << endl << endl;

	// ������ �̸�
	cout << "�̸�: ";
	cin.ignore(256,'\n');
	getline(cin, name);
	cout << "ID: " << idCount + 1;
	
	// ������ ��� �߰�
	cout << endl<< endl << "��Ḧ �߰��մϴ�. ";
	cout << "��Ḧ �Է��ϼ���. ex) ��� 1 ��";

	while (1) {

		Ingredient tempI = Ingredient::readFromInput();
		ingredients.push_back(tempI);

		cout << endl;
		cout << "1. ��� �߰�\t2. �丮�� �ۼ�\tYour Choice: ";

		cin >> choice;

		if (choice == 1)
			continue;
		else if (choice == 2)
			break;
		// ���κ� �̰Ŵ� ���߿� Ű �Է� �޾Ƽ� ����ġ�°ɷ� �ٲٸ� ����ó�� ���ʿ������
	}

	cout << "Ingredient List �ۼ� �Ϸ�" << endl << endl;		// test line

	system("cls");
	// �丮�� �Է�
	cout << "�丮���� ������� �Է��ϼ���. " << endl;
	while (1) {
		string tempAlg;

		cout << endl;

		// �丮�� ����
		cin.ignore(256, '\n');
		getline(cin, tempAlg);			
		cookingAlg.push_back(tempAlg);

		cout << endl << "1. �丮�� �߰�\t2. Finish\tYour Choice: ";

		cin >> choice;

		if (choice == 1)
			continue;
		else if (choice == 2)
			break;
		// ���κ� �̰Ŵ� ���߿� Ű �Է� �޾Ƽ� ����ġ�°ɷ� �ٲٸ� ����ó�� ���ʿ������
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

	Tokenize(parsingLine, tokens, "/");//�Ľ��Ѱ� tokens�ȿ� ��.

									   //�������̸�
	this->nameR = tokens.at(0);
	//������ ���̵�
	this->idR = atoi(tokens.at(1).c_str());

	//������ ���
	vector<string> ingredients;//����
	vector<string> ingreEx;//��� �̸�, ����, ����
	Tokenize(tokens.at(2), ingredients, "$");
	for (int i = 0; i < ingredients.size(); i++) {
		ingreEx.clear();
		Tokenize(ingredients.at(i), ingreEx, "@");
		this->ingredients.push_back(Ingredient (ingreEx.at(0), atoi(ingreEx.at(1).c_str()), ingreEx.at(2)));
	}

	//�丮��
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


// ��� �̸�, ����, ���� ���
void Recipe::printIngredients() {
	for (int i = 0; i<ingredients.size(); i++) {
		cout << ingredients.at(i).getNameI() << " " << ingredients.at(i).getNumI() << " " << ingredients.at(i).getUnitI() << "\n";
	}
	cout << endl;
}

// ��� �̸�, ����*�����, ���� ��� 
void Recipe::printIngredients(int num) {
	for (int i = 0; i < ingredients.size(); i++) {
		cout << ingredients.at(i).getNameI() << ingredients.at(i).getNumI() * num << ingredients.at(i).getUnitI();
	}
}

// ��� �̸� ���
void Recipe::printIngre() {
	for (int i = 0; i<ingredients.size(); i++) {
		cout << i + 1 << ") " << ingredients.at(i).getNameI() << endl;
	}
	cout << endl;
}

//edit ȭ����ȯ, ���� ����� -�ݺ� ���� ���� ���� ��(���� ��) ������ �� �ֵ���, �ڷ� ���� ������ ȭ���� ������ȵ�
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
			//go to greeter greeter ��ü �θ���

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

// ������ ���� �� edit ingredients(add, delete, edit)
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

	//db�� ����� ingredient����Ʈ ����Ͽ� �߰�����, ���� �߰�����
	else if (selectNum == 2 || selectNum == 3) {
		cout << "Select the number you want to delete/edit : ";
		cin >> ingredientNum;

		if (selectNum == 2) {
			ingredients.erase(ingredients.begin() + ingredientNum - 1);
		}
		else if (selectNum == 3) {
			ingredients.erase(ingredients.begin() + ingredientNum - 1);
			addIngredient(); // add�� �������� �� �� �ƴϸ� �����Ǵ� ��ġ�� �� �� ���� *****

			//cin >> ingredients.insert(ingredientNum,);
			//���� �� ���ο� ��ü�� ����. ���ο� ��ü�� ���Ϲ޾ƾ���
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
		cout << "�߰��� ������ �Է��� �ּ���.\n";
		cin.ignore(256, '\n');
		getline(cin, newAlg);
		if (algNum - 1 < cookingAlg.size()) {
			cookingAlg.insert(cookingAlg.begin() + algNum - 1, newAlg);
		}
		else if (algNum - 1 == cookingAlg.size()) {
			cookingAlg.push_back(newAlg);
		}
		else
			cout << "���ڰ� �����ϴ�.\n";

	}
	//db�� ����� ingredient����Ʈ ����Ͽ� �߰�����, ���� �߰�����
	else if (selectNum == 2) {
		cookingAlg.erase(cookingAlg.begin() + algNum - 1);
	}
	else if (selectNum == 3) {
		cout << "������ ������ �Է��� �ּ���.\n";
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
	// �� ù ���ڰ� �������� ��� ����
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// �����ڰ� �ƴ� ù ���ڸ� ã�´�
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos)
	{
		// token�� ã������ vector�� �߰��Ѵ�
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		// �����ڸ� �پ�Ѵ´�.
		lastPos = str.find_first_not_of(delimiters, pos);
		// ���� �����ڰ� �ƴ� ���ڸ� ã�´�
		pos = str.find_first_of(delimiters, lastPos);
	}
}
