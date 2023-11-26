#include "rentrequest.h"
#include "config.h"
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

bool RentRequest::confirmCarAndCost() {
	int     costCentDollars = getDistanceInKm(startLocation, endLocation) * carType.cost;
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
	               .arg(selectedCar.brand)
	               .arg(selectedCar.name)
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
		QTextStream(stdout) << "Payment operation completed successfully\n";
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
	if (!selectCar()) {
		//claudio
		//TODO IMP
	}
	if (!confirmCarAndCost()) {
		return;
	}
	if (!confirmAndMakePayment()) {
		return;
	}
	//claudio
}
