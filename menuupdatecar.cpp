#include "menuupdatecar.h"
#include <QTextStream>
#include <iostream>
#include <validate.h>

void ActionUpdateCar::updateInDb() {
	car->updateInDb();
	QTextStream(stdout) << "Car updated successfully:" << Qt::endl;
	car->printAsTable();
	printEmptyLineSeparator();
}

void ActionUpdateType::run() {
	car->setTypeFromTerminal();
	updateInDb();
};

void ActionUpdateLicensePlate::run() {
	car->setLicensePlateFromTerminal();
	updateInDb();
};

void ActionUpdateBrand::run() {
	car->setBrandFromTerminal();
	updateInDb();
};

void ActionUpdateNameOfCar::run() {
	car->setNameFromTerminal();
	updateInDb();
};

void ActionUpdateLocation::run() {
	car->setLocationFromTerminal();
	updateInDb();
};

void ActionUpdateDistanceTraveled::run() {
	car->setDistanceTraveledFromTerminal();
	updateInDb();
};

MenuUpdateCar::MenuUpdateCar(string label_, Car* car_)
    : Menu(label_) {
	car = car_;

	title = "UPDATE CAR";
	addItem(make_unique<ActionUpdateType>("Update the type", car));
	addItem(make_unique<ActionUpdateLicensePlate>("Update the license plate", car));
	addItem(make_unique<ActionUpdateBrand>("Update the brand", car));
	addItem(make_unique<ActionUpdateNameOfCar>("Update the name", car));
	if (car->locationId) {
		// admin can update the location of a car only when it is not rented (parked in a pick-up point)
		addItem(make_unique<ActionUpdateLocation>("Update the location", car));
	}
	addItem(make_unique<ActionUpdateDistanceTraveled>("Update the total distance traveled", car));
	exitLabel = "End the update operation";
}
