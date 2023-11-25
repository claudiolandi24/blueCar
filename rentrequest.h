#ifndef RENTREQUEST_H
#define RENTREQUEST_H

#include "cartype.h"
#include "location.h"

class RentRequest
{
public:
    CarType carType;
    int numbPersons = 0;
    Location startLocation;
    Location endLocation;
    
    
    RentRequest() = default;
    static RentRequest getFromTerminal();
};

#endif // RENTREQUEST_H
