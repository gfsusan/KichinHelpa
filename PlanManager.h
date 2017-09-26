#pragma once
#include "Date.h"
#include "Meal.h"

#include <vector>
#include <iostream>
#include <ctime>
#include <string>

#define MAX 100
using namespace std;

class PlanManager {
public:
	static PlanManager* instance();
	
	//PlanManager(int yy, int mm, int dd, string plan);
	~PlanManager();

	void timeToCalendar();
	void timeToCalendar(int yy, int mm, int dd, int t);
	void calendar(int yy, int mm, int dd, int HH);

	void planlist(int year, int month, int day, int term);
	void list(int year, int month, int day);
	
	void insertPlan(Date date);
	void browsePlan();
	void deletePlan(int i);
	void editPlan(int i);
	void editDate(int i);

	int viewYear(int i);
	int viewMonth(int i);
	int viewDay(int i);
	Meal viewMeal(int i);
	string viewPlan(int i);
	int viewNumP(int i);

	void PlanManager::writeToFile();
	void PlanManager::readFromFile();

private:
	PlanManager();
	static PlanManager* ptrPM;

	vector <Date> date;
	vector <Meal> meal;
};
