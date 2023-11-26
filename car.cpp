#include "car.h"
#include "cartype.h"
#include "location.h"
#include "menu.h"
#include "menuupdatecar.h"
#include "rbk/minMysql/min_mysql.h"
#include "rbk/misc/b64.h"
#include "utilityfunctions.h"
#include "validate.h"
#include "variadictable.h"
#include <QPair>
#include <QTextStream>
#include <iostream>
#include "rentedcarview.h"

using namespace std;

extern DB db;

Car::Car() {
	entityName = "car";
	table      = "car";
}

Car Car::getCarFromSqlRow(const sqlRow& row) {
	Car car;
	row.get2("id", car.id);
	row.get2("active", car.active);
	row.get2("carTypeId", car.typeId);
	row.get2("licensePlate", car.licensePlate);
	row.get2("brand", car.brand);
	row.get2("name", car.name);
	row.get2("locationId", car.locationId);
	row.get2("totalDistanceTraveled", car.totalDistanceTraveled);
	return car;
}

void Car::setTypeFromTerminal() {
	//claudio
	typeId = getValidatedInt("Insert the car 'type'", make_unique<ValidateCarType>(0));
}

void Car::setLicensePlateFromTerminal() {
	licensePlate = getValidatedString("Insert the car 'license plate'", make_unique<ValidateGeneralAlphaNum>());
}

void Car::setBrandFromTerminal() {
	brand = getValidatedString("Insert the car 'brand'", make_unique<ValidateGeneralAlphaNum>());
}

void Car::setNameFromTerminal() {
	name = getValidatedString("Insert the car 'name'", make_unique<ValidateGeneralAlphaNum>());
}

void Car::setLocationFromTerminal() {
	locationId = getValidatedInt("Insert the current car 'location'", make_unique<ValidateLocation>());
}

void Car::setDistanceTraveledFromTerminal() {
	totalDistanceTraveled = getValidatedInt("Insert the total distance traveled by the car", make_unique<ValidatePositiveOrZeroInteger>());
}

Car Car::getNewCarFromTerminal() {
	Car car;
	car.setTypeFromTerminal();
	car.setLicensePlateFromTerminal();
	car.setBrandFromTerminal();
	car.setNameFromTerminal();
	car.setLocationFromTerminal();
	car.setDistanceTraveledFromTerminal();

	return car;
}

void Car::saveToDb() {
	QString skel = R"(
INSERT INTO car
SET active = %1,
    carTypeId = %2,
    licensePlate = %3,
    brand = %4,
    name = %5,
    locationId = %6,
    totalDistanceTraveled = %7;
)";
	auto    sql  = skel
	               .arg(active)
	               .arg(typeId)
	               .arg(base64this(licensePlate))
	               .arg(base64this(brand))
	               .arg(base64this(name))
	               .arg(locationId)
	               .arg(totalDistanceTraveled);
	db.query(sql);
	id = int(db.lastId());
}

void Car::updateInDb() {
	QString skel = R"(
UPDATE car SET
    active = %1,
    carTypeId = %2,
    licensePlate = %3,
    brand = %4,
    name = %5,
    locationId = %6,
    totalDistanceTraveled = %7
WHERE id = %8;
)";
	auto    sql  = skel
	               .arg(active)
	               .arg(typeId)
	               .arg(base64this(licensePlate))
	               .arg(base64this(brand))
	               .arg(base64this(name))
	               .arg(locationId)
	               .arg(totalDistanceTraveled)
	               .arg(id);
	db.query(sql);
}

void Car::printAsTable() {
	printCarsAsTable({*this});
}

QString Car::locationName() const {
    if(locationId){
        return Location::getLocationNameHuman(locationId);
    }
    return "N/A";
}

QString Car::availability() const {
	return locationId ? "free" : "rented";
}

void Car::updateCarAfterRequest() {
	auto carId = getIdFromTerminal("update");
	if (!carId.first) {
		QTextStream(stdout) << "Update operation canceled" << Qt::endl;
		return;
	}

	auto carList = getCarsFromDb(QSL("id = %1").arg(carId.second));
	Car  car     = carList[0];
	QTextStream(stdout) << "Updating car:" << Qt::endl;

	car.printAsTable();

	MenuUpdateCar menuUpdate("", &car);
	menuUpdate.run();
}

QList<Car> Car::getCarsFromDb(const QString& whereCondition) {
	QString sql = "select * from car where active = 1";
	if (!whereCondition.isEmpty()) {
		sql += " " + whereCondition;
	}
	sql += ";";
	auto res = db.query(sql);

	QList<Car> cars;
	for (const auto& row : res) {
		cars.push_back(Car::getCarFromSqlRow(row));
	}

	return cars;
}

void Car::printCarsAsTable(const QList<Car>& cars) {
	VariadicTable<int, string, string, string, string, string, string, int, string> table(
	    {"Id",
	     "Type",
	     "License Plate",
	     "Brand",
	     "Name",
	     "Availability",
	     "Location",
	     "Total Distance Traveled",
         "Next Service Date"},
	    10);
	for (const auto& car : cars) {
		table.addRow(car.id,
		             CarType::getTypeNameHuman(car.typeId).toStdString(),
		             car.licensePlate.toStdString(),
		             car.brand.toStdString(),
		             car.name.toStdString(),
		             car.availability().toStdString(),
		             car.locationName().toStdString(),
		             car.totalDistanceTraveled,
                     getNextServiceDateString(car.id).toStdString());
	}
	table.print(std::cout);
}

void Car::printAllCarsAsTable() {
	auto cars = getCarsFromDb();
	printCarsAsTable(cars);
}


