#include "car.h"
#include "menu.h"
#include "menuupdatecar.h"
#include "rbk/minMysql/min_mysql.h"
#include "rbk/misc/b64.h"
#include "utilityfunctions.h"
#include "variadictable.h"
#include <QPair>
#include <QTextStream>
#include <iostream>

using namespace std;

extern DB db;

class ValidateGeneralAlphaNum : public Validate {
	QPair<bool, QString> getValidatedString(const QString& string) override {
		bool ok = isAlphanumeric(string, 100);
		if (!ok) {
			return {false, QString()};
		}
		return {true, string};
	}
};

class ValidatePositiveOrZeroInteger : public Validate {
	QPair<bool, int> getValidatedInt(const QString& string) override {
		bool ok;
		int  n = string.toInt(&ok);
		if (!ok) {
			return {false, 0};
		}
		if (n < 0) {
			return {false, 0};
		}
		return {true, n};
	}
};

class ValidateType : public Validate {
	QPair<bool, int> getValidatedInt(const QString& string) override {
		int typeId = getTypeId(string);
		if (!typeId) {
			return {false, 0};
		}
		return {true, typeId};
	}
};

class ValidateLocation : public Validate {
	QPair<bool, int> getValidatedInt(const QString& string) override {
		int locationId = getLocationId(string);
		if (!locationId) {
			return {false, 0};
		}
		return {true, locationId};
	}
};

Car Car::getCarFromSqlRow(sqlRow row) {
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

Car Car::getNewCarFromUser() {
	Car car;
	// type
	car.typeId = getValidatedInt("Insert the car 'type': ECO, MID-CLASS or DELUXE", make_unique<ValidateType>());
	// license plate
	car.licensePlate = getValidatedString("Insert the car 'license plate'", make_unique<ValidateGeneralAlphaNum>());
	// brand
	car.brand = getValidatedString("Insert the car 'brand'", make_unique<ValidateGeneralAlphaNum>());
	// name
	car.name = getValidatedString("Insert the car 'name'", make_unique<ValidateGeneralAlphaNum>());
	// location
	car.locationId = getValidatedInt("Insert the current car 'location': 'Inner Circle', 'Middle Circle' or 'Outer Circle'", make_unique<ValidateLocation>());
	// total distance traveled
	car.totalDistanceTraveled = getValidatedInt("Insert the total distance traveled by the car", make_unique<ValidatePositiveOrZeroInteger>());

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
	auto    sql  = skel.arg(typeId)
	               .arg(base64this(licensePlate))
	               .arg(base64this(brand))
	               .arg(base64this(name))
	               .arg(isFree)
	               .arg(locationId)
	               .arg(totalDistanceTraveled);
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

void Car::deleteCarAfterUserRequest() {
	auto carId = getCarIdFromUser("remove");
	if (!carId.first) {
		QTextStream(stdout) << "Remove operation cancelled" << Qt::endl;
		return;
	}
	deleteCarFromDb(carId.second);
	QTextStream(stdout) << "Car removed successfully" << Qt::endl;
}

void Car::updateCarAfterUserRequest() {
	auto carId = getCarIdFromUser("update");
	if (!carId.first) {
		QTextStream(stdout) << "Update operation cancelled" << Qt::endl;
		return;
	}

	auto carList = getCarsFromDb(QSL("where id = %1").arg(carId.second));
	Car  car     = carList[0];
	QTextStream(stdout) << "Updating car:" << Qt::endl;
	printCarsAsTable({car});

	MenuUpdateCar menuUpdate("",car);
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
	    {"id",
	     "type",
	     "licensePlate",
	     "brand",
	     "name",
	     "availability",
	     "location",
	     "totalDistanceTraveled"},
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
