#include "menumanagecar.h"
#include <iostream>

void ActionAddCar::run() {
	cout << "running add car" << endl;
	printEmptyLineSeparator();
};

void ActionUpdateCar::run() {
	cout << "running update car" << endl;
	printEmptyLineSeparator();
};

void ActionRemoveCar::run() {
	cout << "running remove car" << endl;
	printEmptyLineSeparator();
};

void ActionShowCars::run() {
	cout << "running show cars" << endl;
	printEmptyLineSeparator();
};

MenuManageCar::MenuManageCar(string label_)
    : Menu(label_) {
	title = "MANAGE CARS";
	addItem(make_unique<ActionAddCar>("Add car"));
	addItem(make_unique<ActionUpdateCar>("Update car"));
	addItem(make_unique<ActionRemoveCar>("Remove car"));
	addItem(make_unique<ActionShowCars>("Show cars"));
}
