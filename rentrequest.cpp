#include "rentrequest.h"
#include <QTextStream>
#include "validate.h"


RentRequest RentRequest::getFromTerminal() {
    RentRequest request;
    
    
    
    int carTypeId = getValidatedInt("Insert the car 'type'", make_unique<ValidateCarType>());
    request.carType = CarType::fromId(carTypeId);
    
    //claudio
    
}
