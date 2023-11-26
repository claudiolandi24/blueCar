#include "rentrequest.h"
#include "location.h"
#include "rbk/minMysql/min_mysql.h"
#include "validate.h"
#include <QTextStream>

extern DB db;

bool RentRequest::selectCar() {
	// Metric: prefer cars with few km travelled
	QString skel = R"(
SELECT *
FROM freeCarView
WHERE carTypeId = %1 AND locationId = %2
ORDER BY totalDistanceTraveled ASC
LIMIT 1;
)";
	auto    sql  = skel
	               .arg(carType.id)
	               .arg(startLocation.id);
	auto res = db.query(sql);
	if (res.isEmpty()) {
		return false;
	}
	selectedCar = Car::getCarFromSqlRow(res[0]);
	return true;
}

bool RentRequest::carAndCostAreOk() {
}

bool makePayment() {
}

void RentRequest::updateDb() {
}

RentRequest RentRequest::getFromTerminal() {
	RentRequest request;

	// numb persons
	request.numbPersons = getValidatedInt("Insert the number of persons will be in the car", make_unique<ValidateNumbPersons>());
	// car type
	int carTypeId   = getValidatedInt("Insert the car 'type'", make_unique<ValidateCarType>(request.numbPersons));
	request.carType = CarType::fromId(carTypeId);

	// start
	int startLocationId   = getValidatedInt("Insert the start location'", make_unique<ValidateLocation>());
	request.startLocation = Location::fromId(startLocationId);

	// end
	int endLocationId   = getValidatedInt("Insert the end location'", make_unique<ValidateLocation>());
	request.endLocation = Location::fromId(endLocationId);

	return request;
}

void RentRequest::run() {
}
