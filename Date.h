#pragma once
#include "Meal.h"

#include <iostream>
#include <string>
#include <vector>


using namespace std;

class Date {
private:
	int year;
	int month;
	int day;
	int numP;
	Meal meal;
	string plan;

public:
	Date();
	Date(int y, int m, int d, int numP, Meal meal);
	Date(int y, int m, int d, int numP, Meal meal, string plan);
	Date(string parsingLine);
	~Date();

	static Date readFromInput();
	void Tokenize(const string& str, vector<string>& tokens, const string& delimiters);

	int getYear();
	int getMonth();
	int getDay();
	int getNumP();
	string getPlan();
	Meal getMeal();

	void editDate(int year, int month, int day, int num, string plan);
	void editDate(int year, int month, int day, int num);

};
