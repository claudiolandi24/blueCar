#include "car.h"
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

using namespace std;

extern DB db;

Car Car::getCarFromSqlRow(const sqlRow& row) {
	Car car;
	row.get2("id", car.id);
	row.get2("typeId", car.typeId);
	row.get2("licensePlate", car.licensePlate);
	row.get2("brand", car.brand);
	row.get2("name", car.name);
	row.get2("isFree", car.isFree);
	row.get2("locationId", car.locationId);
	row.get2("totalDistanceTraveled", car.totalDistanceTraveled);
	return car;
}

void Car::setTypeFromTerminal() {
	typeId = getValidatedInt("Insert the car 'type'", make_unique<ValidateCarType>());
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
SET typeId = %1,
    licensePlate = %2,
    brand = %3,
    name = %4,
    isFree = %5,
    locationId = %6,
    totalDistanceTraveled = %7;
)";
	auto    sql  = skel
	               .arg(typeId)
	               .arg(base64this(licensePlate))
	               .arg(base64this(brand))
	               .arg(base64this(name))
	               .arg(isFree)
	               .arg(locationId)
	               .arg(totalDistanceTraveled);
	db.query(sql);
}

void Car::updateInDb() {
	QString skel = R"(
UPDATE car SET
    typeId = %1,
    licensePlate = %2,
    brand = %3,
    name = %4,
    locationId = %5,
    totalDistanceTraveled = %6
WHERE id = %7;
)";
	auto    sql  = skel
	               .arg(typeId)
	               .arg(base64this(licensePlate))
	               .arg(base64this(brand))
	               .arg(base64this(name))
	               .arg(locationId)
	               .arg(totalDistanceTraveled)
	               .arg(id);
	db.query(sql);
}

bool Car::carIdExists(int carId) {
	QString skel = R"(
select * from car where id = %1; 
)";
	auto    sql  = skel.arg(carId);
	auto    res  = db.query(sql);
	if (res.empty()) {
		return false;
	}
	return true;
}

QPair<bool, int> Car::getCarIdFromUser(const QString& operation) {
	if (operation != "update" and operation != "remove") {
		//TODO log error
		return {false, 0};
	}

	QString msgSkel = R"(Insert the ID of the car you want to %1.
Insert 0 (zero) to cancel this operation)";
	auto    msg     = msgSkel.arg(operation);
	QTextStream(stdout) << msg << Qt::endl;
	QString rawInput = QTextStream(stdin).readLine();
	bool    ok;
	int     carId = rawInput.toInt(&ok);
	if (!ok) {
		QTextStream(stdout) << "The inserted value is not a valid number" << Qt::endl;
		return {false, 0};
	}
	if (!carIdExists(carId)) {
		QTextStream(stdout) << QSL("No car with ID %1").arg(carId) << Qt::endl;
		return {false, 0};
	}

	return {true, carId};
}

void Car::deleteCarFromDb(int id) {
	QString sql = QSL("DELETE FROM car WHERE id = %1;").arg(id);
	db.query(sql);
}

void Car::deleteCarAfterRequest() {
	auto carId = getCarIdFromUser("remove");
	if (!carId.first) {
		QTextStream(stdout) << "Remove operation cancelled" << Qt::endl;
		return;
	}
	deleteCarFromDb(carId.second);
	QTextStream(stdout) << "Car removed successfully" << Qt::endl;
}

void Car::printAsTable() {
	printCarsAsTable({*this});
}

void Car::updateCarAfterRequest() {
	auto carId = getCarIdFromUser("update");
	if (!carId.first) {
		QTextStream(stdout) << "Update operation cancelled" << Qt::endl;
		return;
	}

	auto carList = getCarsFromDb(QSL("where id = %1").arg(carId.second));
	Car  car     = carList[0];
	QTextStream(stdout) << "Updating car:" << Qt::endl;

	car.printAsTable();

	MenuUpdateCar menuUpdate("", car);
	menuUpdate.run();

	//QTextStream(stdout) << "Car updated successfully" << Qt::endl;
}

QList<Car> Car::getCarsFromDb(const QString& whereCondition) {
	auto sqlSkel = QSL("select * from car %1;");
	auto sql     = sqlSkel.arg(whereCondition);
	auto res     = db.query(sql);

	QList<Car> cars;
	for (const auto& row : res) {
		cars.push_back(Car::getCarFromSqlRow(row));
	}

	return cars;
}

void Car::printCarsAsTable(const QList<Car>& cars) {
	VariadicTable<int, string, string, string, string, string, string, int> table(
	    {"Id",
	     "Type",
	     "License Plate",
	     "Brand",
	     "Name",
	     "Availability",
	     "Location",
	     "Total Distance Traveled"},
	    10);
	for (const auto& car : cars) {
		table.addRow(car.id,
		             getTypeNameHuman(car.typeId).toStdString(),
		             car.licensePlate.toStdString(),
		             car.brand.toStdString(),
		             car.name.toStdString(),
		             getAvailabilityHuman(car.isFree).toStdString(),
		             getLocationNameHuman(car.locationId).toStdString(),
		             car.totalDistanceTraveled);
	}
	table.print(std::cout);
}

void Car::printAllCarsAsTable() {
	auto cars = getCarsFromDb();
	printCarsAsTable(cars);
}
