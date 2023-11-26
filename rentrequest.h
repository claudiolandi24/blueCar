#ifndef RENTREQUEST_H
#define RENTREQUEST_H

#include "car.h"
#include "cartype.h"
#include "location.h"

class RentRequest
{
private:
    bool selectCar();
    bool carAndCostAreOk();
    bool makePayment();
    void updateDb();
public:
    CarType carType;
    int numbPersons = 0;
    Location startLocation;
    Location endLocation;
    
    Car selectedCar;
    
    
    
    RentRequest() = default;
    static RentRequest getFromTerminal();
    void run();
};

#endif // RENTREQUEST_H
