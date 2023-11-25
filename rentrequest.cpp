#include "rentrequest.h"
#include "location.h"
#include "validate.h"
#include <QTextStream>

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
	//claudio
}
