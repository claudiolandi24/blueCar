#include "rentrequest.h"
#include <QTextStream>
#include "validate.h"


RentRequest RentRequest::getFromTerminal() {
    QTextStream(stdout) << "Select ";//claudio
    int carTypeId = getValidatedInt("Insert the car 'type'", make_unique<ValidateCarType>());
    
    
    
}
