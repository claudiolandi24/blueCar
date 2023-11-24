#include "menumanagecar.h"
#include "car.h"
#include <QTextStream>
#include <iostream>

void ActionAddCar::run() {
	cout << "--- ADD CAR ---" << endl;
	Car newCar = Car::getNewCarFromTerminal();
	newCar.saveToDb();
	QTextStream(stdout) << "Car added successfully" << Qt::endl;

	printEmptyLineSeparator();
};

void ActionUpdateCar::run() {
	cout << "--- UPDATE CAR ---" << endl;
    Car::updateCarAfterUserRequest();
    
	printEmptyLineSeparator();
};

void ActionRemoveCar::run() {
	cout << "--- REMOVE CAR ---" << endl;
	Car::deleteCarAfterRequest();

	printEmptyLineSeparator();
};

MenuManageCar::MenuManageCar(string label_)
    : Menu(label_) {
	title = "MANAGE CARS";
	addItem(make_unique<ActionAddCar>("Add car"));
	addItem(make_unique<ActionUpdateCar>("Update car"));
	addItem(make_unique<ActionRemoveCar>("Remove car"));
}

void MenuManageCar::actionBeforeShow() {
	Car::printAllCarsAsTable();
	cout << "\n";
}
