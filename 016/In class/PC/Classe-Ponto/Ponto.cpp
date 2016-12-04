#include "Ponto.h"
#include <iostream>
#include <math.h>

using namespace std;

char Ponto::contId = 'A';
Ponto::Ponto(int a, int b):id(contId++) {
	if (!this->setX(a) || !this->setY(b)) {
		this->setX(0);
		this->setY(0);
	}
	this->declared = false;
}
int Ponto::getX() const {
	return this->x;
}
int Ponto::getY() const {
	return this->y;
}
char Ponto::getId() const {
	return this->id;
}
bool Ponto::getDeclared() const {
	return this->declared;
}
bool Ponto::setX(int a) {
	this->declared = true;
	if (a > -((this->cols / 2) + (1 / 2)) && a < (this->cols / 2) + (1 / 2)) {
		this->x = a;
		return true;
	} else
		return false;
}
bool Ponto::setY(int b) {
	this->declared = true;
	if (b > -((this->rows / 2) + (1 / 2)) && b < (this->rows / 2) + (1 / 2)) {
		this->y = b;
		return true;
	} else {
		return false;
	}
}
void Ponto::operator=(Ponto A) {
	this->setX(A.getX());
	this->setY(A.getY());
}
void Ponto::delPoint() {
	this->setX(0);
	this->setY(0);
	this->declared = false;
}
Ponto middPoint(Ponto A, Ponto B) {
	Ponto M;
	M.setX((A.getX() + B.getX()) / 2);
	M.setY((A.getY() + B.getY()) / 2);
	return M;
}
bool isColli(Ponto A, Ponto B, Ponto C) {
	if (A.x * B.y + A.y * C.x + B.x * C.y - C.x * B.y - A.x * C.y - B.x * A.y)
		return false;
	else
		return true;
}
double distPoints(Ponto A, Ponto B) {
	return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
}
void Ponto::print() {
	cout << "(" << this->x << ", " << this->y << ")" << endl;
}
