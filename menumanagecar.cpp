#include "menumanagecar.h"
#include <iostream>
#include "car.h"

void ActionAddCar::run() {
	cout << "--- ADD CAR ---" << endl;
    Car newCar = Car::getNewCarFromUser();
    newCar.saveToDb();
    
	printEmptyLineSeparator();
};

void ActionUpdateCar::run() {
	cout << "running update car" << endl;
	printEmptyLineSeparator();
};

void ActionRemoveCar::run() {
	cout << "--- REMOVE CAR ---" << endl;
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
