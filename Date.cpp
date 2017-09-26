#include "Date.h"

Date::Date() {

}


Date::Date(int y, int m, int d, int p, Meal meal) {
	this->year = y;
	this->month = m;
	this->day = d;
	this->numP = p;
	this->meal = meal;
	this->plan = "*";

}

Date::Date(int y, int m, int d, int p, Meal meal, string plan) {
	this->year = y;
	this->month = m;
	this->day = d;
	this->numP = p;
	this->meal = meal;
	this->plan = plan;

}

Date ::~Date() {
}

void Date::editDate(int year, int month, int day, int num) {
	this->year = year;
	this->month = month;
	this->day = day;
	this->numP = num;
	this->plan = "*";

}

void Date::editDate(int year, int month, int day, int people, string plan) {
	this->year = year;
	this->month = month;
	this->day = day;
	this->plan = plan;
	this->numP = people;

}

Date Date::readFromInput() {
	int year, month, day, people;
	char check, choice;
	Meal tempMeal;
	string plan;
	cout << "Input Date (YYYY MM DD) : ";
	cin >> year;
	cin >> month;
	cin >> day;
	cout << "input people number";
	cin >> people;

	cout << "If you want to create Meal, input 'C'.\n";
	cout << "If you want computer to create meal automatically, input 'A' : ";

	while (1) {
		cin >> choice;
		if (choice == 'C' || choice == 'c') {
			tempMeal.makeMealP();
			break;
		}
		else if (choice == 'A' || choice == 'a') {
			tempMeal.makeMealC();
			break;
		}
		else {
			cout << "You wrote wrong character" << endl;
		}
	}


	cout << "If you want to write plan, input 'Y'. Otherwise, input 'X'. : ";
	cin >> check;

	if (check == 'Y') {
		cin.ignore(256, '\n');
		cout << "plan : ";
		getline(cin, plan);

		return Date(year, month, day, people, tempMeal, plan);
	}
	else {
		return Date(year, month, day, people, tempMeal);

	}
}


int Date::getYear() {
	return this->year;
}

int Date::getMonth() {
	return this->month;
}

int Date::getDay() {
	return this->day;
}

string Date::getPlan() {
	return this->plan;
}

Meal Date::getMeal() {
	return this->meal;
}


int Date::getNumP() {
	return this->numP;
}


Date::Date(string parsingLine) {
	vector<string> tokens;

	Tokenize(parsingLine, tokens, "/");//�Ľ��Ѱ� tokens�ȿ� ��.

									   //��/��/�� �Ľ��غ���
	vector<string> date;//��/��/���� ��Ʈ�������� ����Ǵ� ����
	Tokenize(tokens.at(0), date, "&");
	this->year = atoi(date.at(0).c_str());
	this->month = atoi(date.at(1).c_str());
	this->day = atoi(date.at(2).c_str());

	//�����
	this->numP = atoi(tokens.at(1).c_str());

	//mealID �Ľ��غ���
	vector<string> mealIdStr;//mealId�� �Ľ̵Ǿ� ��Ʈ�������� ����Ǵ� ����
	Tokenize(tokens.at(2), mealIdStr, "&");
	for (int i = 0; i < mealIdStr.size(); i++)
	{
		// �������پȵż�
		meal.pushMealId(atoi(mealIdStr.at(i).c_str()));
		//maelIdStr�� int������ �ٲپ� meallist�� �־��ش�
	}

	//����ȵ���
	this->plan = tokens.at(3);
}
void Date::Tokenize(const string& str, vector<string>& tokens, const string& delimiters) {
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