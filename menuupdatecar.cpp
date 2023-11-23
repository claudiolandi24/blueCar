#include "menuupdatecar.h"
#include <QTextStream>
#include <iostream>
#include <validate.h>

void ActionUpdateCar::updateInDb() {
	car.updateInDb();
	QTextStream(stdout) << "Car updated successfully:" << Qt::endl;
	car.printAsTable();
	printEmptyLineSeparator();
}

void ActionUpdateType::run() {
	car.setTypeFromUser();
	updateInDb();
};

void ActionUpdateLicensePlate::run() {
	car.setLicensePlateFromUser();
	updateInDb();
};

void ActionUpdateBrand::run() {
	car.setBrandFromUser();
	updateInDb();
};

void ActionUpdateName::run() {
	car.setNameFromUser();
	updateInDb();
};

void ActionUpdateLocation::run() {
	car.setLocationFromUser();
	updateInDb();
};

void ActionUpdateDistanceTraveled::run() {
	car.setDistanceTraveledFromUser();
	updateInDb();
};

//TODO
// check empty lines separator in interaction
// some missing
MenuUpdateCar::MenuUpdateCar(string label_, Car car_)
    : Menu(label_) {
	car = car_;

	title = "UPDATE CAR";
	addItem(make_unique<ActionUpdateType>("Update the type", car));
	addItem(make_unique<ActionUpdateLicensePlate>("Update the license plate", car));
	addItem(make_unique<ActionUpdateBrand>("Update the brand", car));
	addItem(make_unique<ActionUpdateName>("Update the name", car));
	//TODO IMP only if free
	addItem(make_unique<ActionUpdateLocation>("Update the location", car));
	addItem(make_unique<ActionUpdateDistanceTraveled>("Update the total distance traveled", car));
	exitLabel = "End the update operation";
}
