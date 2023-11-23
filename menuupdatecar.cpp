#include "menuupdatecar.h"
#include <iostream>

void ActionUpdateType::run() {
	cout << "-type" << endl;
	printEmptyLineSeparator();
};

void ActionUpdateLicensePlate::run() {
	cout << "-licensePlate" << endl;
	printEmptyLineSeparator();
};

void ActionUpdateBrand::run() {
	cout << "-brand" << endl;
	printEmptyLineSeparator();
};

void ActionUpdateName::run() {
	cout << "-name" << endl;
	printEmptyLineSeparator();
};

void ActionUpdateLocation::run() {
	cout << "" << endl;
	printEmptyLineSeparator();
};

void ActionUpdateDistanceTraveled::run() {
	cout << "" << endl;
	printEmptyLineSeparator();
};

MenuUpdateCar::MenuUpdateCar(string label_, Car car_)
    : Menu(label_) {
	car = car_;

	title = "UPDATE CAR";
	addItem(make_unique<ActionUpdateType>("Update the type",car));
	addItem(make_unique<ActionUpdateLicensePlate>("Update the license plate"));
	addItem(make_unique<ActionUpdateBrand>("Update the brand"));
	addItem(make_unique<ActionUpdateName>("Update the name"));
	//TODO IMP only if free
	addItem(make_unique<ActionUpdateLocation>("Update the location"));
	addItem(make_unique<ActionUpdateDistanceTraveled>("Update the total distance traveled"));
	exitLabel = "End the update operation";
}
