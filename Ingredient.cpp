#include "Ingredient.h"

Ingredient Ingredient::readFromInput() {


	// Ingredient()는 Ingredient의 이름, 수량, 단위를 묻는다.
	string name;
	int num;
	string unit;

	cout << endl;

	cout << "이름: ";
	cin >> name;
	cout << "수량: ";
	cin >> num;
	cout << "단위: ";
	cin >> unit;

	// Ingredient(이름, 수량, 단위)를 호출하려 Ingredient 객체 생성
	return Ingredient(name, num, unit);

	cout << "Ingredient 생성 완료";
}

// Ingredient의 이름, 수량, 단위를 입력받아 새로운 Ingredient 객체를 생성
Ingredient::Ingredient(string name, int num, string unit) {

	this->nameI = name;
	this->numI = num;
	this->unitI = unit;
}

// 소멸자
Ingredient::~Ingredient() {}


// 재료 이름 변경
void Ingredient::editNameI(string nameI) {
	this->nameI = nameI;
}

// 재료 수량 변경
void Ingredient::editNumI(int numI) {
	this->numI = numI;
}

// 재료 단위 변경
void Ingredient::editUnitI(string unitI) {
	this->unitI = unitI;
}

// 재료 이름 리턴
string Ingredient::getNameI() {
	return this->nameI;
}

// 재료 수량 리턴
int Ingredient::getNumI() {
	return this->numI;
}

// 재료 단위 리턴
string Ingredient::getUnitI() {
	return this->unitI;
}