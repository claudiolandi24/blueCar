#include "rentrequest.h"
#include <QTextStream>
#include "validate.h"


RentRequest RentRequest::getFromTerminal() {
    RentRequest request;
    
    // numb persons
    request.numbPersons = getValidatedInt("Insert the number of persons will be in the car", make_unique<ValidateNumbPersons>());
    // car type
    int carTypeId = getValidatedInt("Insert the car 'type'", make_unique<ValidateCarType>(request.numbPersons));
    request.carType = CarType::fromId(carTypeId);
    
    //claudio
    
}
