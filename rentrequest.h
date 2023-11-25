#ifndef RENTREQUEST_H
#define RENTREQUEST_H

#include "car.h"
#include "cartype.h"
#include "location.h"

class RentRequest
{
private:
    Car selectCar();
public:
    CarType carType;
    int numbPersons = 0;
    Location startLocation;
    Location endLocation;
    
    
    RentRequest() = default;
    static RentRequest getFromTerminal();
    void run();
};

#endif // RENTREQUEST_H
