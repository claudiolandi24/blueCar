#include "rentrequest.h"
#include "config.h"
#include "location.h"
#include "rbk/minMysql/min_mysql.h"
#include "rent.h"
#include "rentedcarview.h"
#include "service.h"
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
	car = Car::getCarFromSqlRow(res[0]);
	return true;
}

bool RentRequest::confirmCarAndCost() {
	distance                = getDistanceInKm(startLocation, endLocation);
	int     costCentDollars = distance * carType.cost;
	int     costDollar      = costCentDollars / 100;
	QString skel            = R"(This car has been selected:
Type: %1
Brand: %2
Name: %3

The total rent cost is %4 $

Do you want to rent this car? Press 'yes' to rent it or 'no' to cancel the rent operation (Y/N)
)";
	auto    msg             = skel
	               .arg(carType.name)
	               .arg(car.brand)
	               .arg(car.name)
	               .arg(costDollar);
	QTextStream(stdout) << msg;
	if (!yesFromTerminal()) {
		QTextStream(stdout) << "Rent operation canceled\n";
		return false;
	}
	return true;
}

/*
 * Payment operation is simulated.
 * A real application would call an external API to make the payment and send to them some user and credit card data
 */
bool RentRequest::makePayment() {
	if (config::paymentOperationSuccess) {
		QTextStream(stdout) << QSL("Payment operation completed successfully. The car can be collected at the pick-up point of %1\n").arg(startLocation.name);
		return true;
	}
	QTextStream(stdout) << "Error in payment operation. Rent operation canceled\n";
	return false;
}

bool RentRequest::confirmAndMakePayment() {
	QTextStream(stdout) << "The rent will be paid by using the credit card registered in your account. Do you want to make the payment?\n";
	QTextStream(stdout) << "Press 'yes' to make the payment or 'no' to cancel the rent operation (Y/N)\n";
	if (!yesFromTerminal()) {
		QTextStream(stdout) << "Rent operation canceled\n";
		return false;
	}

	return makePayment();
}

int RentRequest::getExactTravelTime() const {
	int time = (secondsPerHour * distance) / carType.speed;
	return time;
}

void RentRequest::updateDb() {
	rent.userId          = user->id;
	rent.carId           = car.id;
	rent.startLocationId = startLocation.id;
	rent.startDateTime   = QDateTime::currentDateTimeUtc();
	rent.endLocationId   = endLocation.id;
	// real endDateTime unknow at this point

	// +50 % margin
	int estimatedTimeInSeconds = int(double(getExactTravelTime()) * 1.5);
	rent.estimatedEndDateTime  = rent.startDateTime.addSecs(estimatedTimeInSeconds);

	rent.distance = distance;
	rent.cost     = cost;

	db.query("START TRANSACTION;");
	rent.saveInDb();
	// Set locationId of the car as NULL
	// When a car is rented its location is unknown
	QString skel = R"(
UPDATE car SET
    locationId = NULL
WHERE id = %1;
)";
	auto    sql  = skel.arg(car.id);
	db.query(sql);
	db.query("COMMIT");
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

void RentRequest::logEndDateTime() {
	// Log endDateTime in rent table
	// Simulate time is +20 % than exact time
	int       timeInSeconds = int(double(getExactTravelTime()) * 1.2);
	QDateTime endDateTime   = rent.startDateTime.addSecs(timeInSeconds);
	auto      sql           = QSL("update rent set endDateTime = %1 where id = %2;")
	               .arg(endDateTime.toString(mysqlDateTimeFormat))
	               .arg(rent.id);
	db.query(sql);
}

void RentRequest::updateCarLocationAndDistanceTraveled() {
	// Update car location and total distance traveled
	car.locationId = endLocation.id;
	car.totalDistanceTraveled += distance;
	car.updateInDb();
}

void RentRequest::scheduleServiceIfNeed() {
	auto sql = QSL("select * from lastServiceView where carId = %1;").arg(car.id);
	auto res = db.query(sql);

	bool needService                 = false;
	int  lastServiceDistanceTraveled = 0;
	if (!res.isEmpty()) {
		res[0].get2("serviceTotalDistanceTraveled", lastServiceDistanceTraveled);
	}
	if (car.totalDistanceTraveled >= lastServiceDistanceTraveled + config::serviceEveryKm) {
		needService = true;
	}
	if (needService) {
		Service::scheduleService(car);
	}
}

void RentRequest::simulateCarIsReturned() {
	db.query(QSL("START TRANSACTION;"));
	logEndDateTime();
	updateCarLocationAndDistanceTraveled();
	scheduleServiceIfNeed();
	db.query(QSL("COMMIT;"));
}

void RentRequest::run() {
	if (!selectCar()) {
        int waitingTimeSecs = getWaitingTime(*this);
        if(waitingTimeSecs!=-1){
            QTextStream(stdout) << "Estimated waiting time " << waitingTimeSecs/secondsPerMinute<<" min\n";
        }
	}
	if (!confirmCarAndCost()) {
		return;
	}
	if (!confirmAndMakePayment()) {
		return;
	}
	updateDb();
	/*
	 * We simulate the return of the car so that after the user rent a car, the software simulates
	 * its return and we can see consistent data in the database.
	 * I.e.
	 * Updated location for the car, update total distance traveled, etc.
	 *
	 * In a real system the return of the car would be managed by another software component and
	 * not now, but in the future when the user will return the car
	 */
	simulateCarIsReturned();
}
