#define _CRT_SECURE_NO_WARNINGS

#include "PlanManager.h"

#include <cstdlib>
#include <fstream>

PlanManager* PlanManager::ptrPM = NULL;

// singleton 
PlanManager* PlanManager::instance() {
	if (ptrPM == NULL)
		ptrPM = new PlanManager();

	return ptrPM;
}
PlanManager::PlanManager() {
	date.clear();
	// 파일을 읽어 스트링을 레시피 객체로 바꾸어주는것  
	readFromFile();
};

PlanManager::~PlanManager() {
	writeToFile();
}


void PlanManager::timeToCalendar() {
	time_t current_time;
	tm *current_tm;
	current_time = time(NULL);
	current_tm = localtime(&current_time);
	calendar(current_tm->tm_year + 1900, current_tm->tm_mon + 1, current_tm->tm_mday, current_tm->tm_hour);

}

void PlanManager::timeToCalendar(int yy, int mm, int day, int t) {
	time_t current_time;
	tm *current_tm;
	current_time = time(NULL);
	current_tm = localtime(&current_time);
	calendar(yy, mm, current_tm->tm_mday, t);

}

void PlanManager::calendar(int yy, int mm, int dd, int t) {
	int count = 1;
	int month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int day = (1 + (int)(13 / 5 * (mm + 1)) + yy + (int)((int)(yy / 100) / 4) + (int)((yy % 100) / 4) - 2 * (yy % 100)) + 1;
	day %= 7;
	cout << "[Sun] [Mon] [Tue] [Wed] [Thu] [Fri] [Sat] " << endl;
	for (int i = 0; i < 42; i++) {
		if (i <= day) {
			cout << "      ";
		}
		else {
			printf("  %2d  ", count);
			count++;
		}
		if (count - 1 == month[mm - 1])
			break;
		if (i % 7 == 0)
			cout << endl;
	}
	cout << endl;
	planlist(yy, mm, dd, t);

}

void PlanManager::insertPlan(Date tempDate) {

	date.push_back(tempDate);
	cout << "플랜 추가 완료." << endl;
}

void PlanManager::browsePlan() {
	//date[i].getPlan();
	int year;
	int month;
	int day;
	int term;

	cout << endl << " input date (YYYY MM DD) : ";
	cin >> year >> month >> day;
	cout << endl << " term : ";
	cin >> term;

	timeToCalendar(year, month, day, term);
}


void PlanManager::planlist(int year, int month, int day, int term) {
	int count = 0;
	int monthAll[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	char input;
	for (int i = 0; i < date.size(); i++) {
		int Y = year, M = month, D = day, T = term;

		for (int j = 0; j < term; j++, D++) {
			if (D > monthAll[M]) {
				D = D - monthAll[M];
				M++;
			}
			if (M == 13)
				M = 1;
			if (date[i].getYear() == Y)
				if (date[i].getMonth() == M)
					if (date[i].getDay() == D) {
						cout << Y << "/" << M << "/" << D << " - " << viewNumP(i) << "people" << endl;
						viewMeal(i).printRecipeName();
						count++;
					}
		}
	}
	if (count == 0) {
		cout << " no plan in date" << endl;
		while (true) {
			cout << " insert new plan? ( Y / N) : ";
			cin >> input;
			if (input == 'Y' || input == 'y') {
				insertPlan(Date::readFromInput());
				break;
			}
			else if (input == 'n' || input == 'N') {
				cout << " cancel";
				break;
			}
			else
				cout << endl << "right ";
		}
	}
	if (count > 0) {
		list(year, month, day);
	}
}

void PlanManager::list(int year, int month, int day) {
	int input = 0;
	for (int i = 0; i < date.size(); i++) {
		cout << "Plan num " << i << " -> " << viewYear(i) << "/" << viewMonth(i) << "/" << viewDay(i) << "  " << viewPlan(i) << endl;
	}
	cout << "input Plan num : ";
	cin >> input;
	if ((input < 0) || (input >= date.size())) {
		cout << "invalid" << endl;
	}
	else
		editPlan(input);

}

void PlanManager::deletePlan(int i) {
	date.erase(date.begin() + i);
}

void PlanManager::editPlan(int i) {
	char input = 0;
	cout << viewYear(i) << "/" << viewMonth(i) << "/" << viewDay(i) << " - " << viewPlan(i) << endl;
	cout << "Edit? (E) Delete? (d) Cancel(else): ";
	while (true)
	{
		cin >> input;
		if (input = 'E' || input == 'e') {
			editDate(i);
			break;
		}
		else if (input = 'D' || input == 'd') {
			deletePlan(i);
			cout << "cancel..";
			break;
		}
		else {
			cout << "input Y or N";
			break;
		}
	}
}

void PlanManager::editDate(int i) {
	int Year, Month, Day, people;
	string plan;
	cout << "year : ";
	cin >> Year;
	cout << "month : ";
	cin >> Month;
	cout << "day : ";
	cin >> Day;
	cout << "people number : ";
	cin >> people;
	cout << "plan : ";

	cin.ignore(256, '\n');
	getline(cin, plan);


	date[i].editDate(Year, Month, Day, people, plan);

}

int PlanManager::viewYear(int i) {
	return date[i].getYear();
}

int PlanManager::viewMonth(int i) {
	return date[i].getMonth();
}

int PlanManager::viewDay(int i) {
	return date[i].getDay();
}


Meal PlanManager::viewMeal(int i) {
	return date[i].getMeal();
}

string PlanManager::viewPlan(int i) {
	return date[i].getPlan();
}

int PlanManager::viewNumP(int i) {
	return date[i].getNumP();
}

void PlanManager::readFromFile() {

	ifstream inPFile("PlanManager.txt", ios::in);
	if (inPFile.is_open()) {

		string line;

		while (getline(inPFile, line)) {
			this->date.push_back(Date(line));
		}
		inPFile.close();
	}
	else cout << "Unable to open PlanFile";

}



void PlanManager::writeToFile() {
	ofstream saving;
	saving.open("PlanManager.txt", ios::out | ios::trunc); //파일 열기,이미 파일이 있으면 삭제하고 새로 만듦 
	Meal plan; //plan은 하나의 date에 대한 플랜

	for (int i = 0; i < date.size(); i++)
	{
		plan = date[i].getMeal();//하나의 meal(하나의 식사계획임)
		string ID;
		vector<int> recipeIDs;


		recipeIDs = plan.getIDList();//하나의 meal에 사용되는 recipeID 벡터를 모두 받아옴.

		for (int j = 0; j < plan.getRecipeIDsize(); j++)
		{
			ID.append("&");//ID스트링에 *를 추가함
			ID.append(to_string(recipeIDs[j]));      //ID 스트링에 recipeID를 추가함(출력하기위해서 하나의 스트링으로 만들어줌)   
		}

		saving << to_string(date[i].getYear()) << "&" << to_string(date[i].getMonth()) << "&" << to_string(date[i].getDay())
			<< "/" << to_string(date[i].getNumP()) << "/" << ID << "/" << date[i].getPlan() << endl;
		//to_string(int ) -> int형 데이터를 string형으로 만들어줌.

		recipeIDs.clear();//recipeID 벡터 지우기.

	}
	saving.close();//파일 닫기
}

