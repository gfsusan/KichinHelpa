#include "Ingredient.h"

Ingredient Ingredient::readFromInput() {


	// Ingredient()�� Ingredient�� �̸�, ����, ������ ���´�.
	string name;
	int num;
	string unit;

	cout << endl;

	cout << "�̸�: ";
	cin >> name;
	cout << "����: ";
	cin >> num;
	cout << "����: ";
	cin >> unit;

	// Ingredient(�̸�, ����, ����)�� ȣ���Ϸ� Ingredient ��ü ����
	return Ingredient(name, num, unit);

	cout << "Ingredient ���� �Ϸ�";
}

// Ingredient�� �̸�, ����, ������ �Է¹޾� ���ο� Ingredient ��ü�� ����
Ingredient::Ingredient(string name, int num, string unit) {

	this->nameI = name;
	this->numI = num;
	this->unitI = unit;
}

// �Ҹ���
Ingredient::~Ingredient() {}


// ��� �̸� ����
void Ingredient::editNameI(string nameI) {
	this->nameI = nameI;
}

// ��� ���� ����
void Ingredient::editNumI(int numI) {
	this->numI = numI;
}

// ��� ���� ����
void Ingredient::editUnitI(string unitI) {
	this->unitI = unitI;
}

// ��� �̸� ����
string Ingredient::getNameI() {
	return this->nameI;
}

// ��� ���� ����
int Ingredient::getNumI() {
	return this->numI;
}

// ��� ���� ����
string Ingredient::getUnitI() {
	return this->unitI;
}