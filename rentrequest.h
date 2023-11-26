#ifndef RENTREQUEST_H
#define RENTREQUEST_H

#include "car.h"
#include "cartype.h"
#include "location.h"

class RentRequest
{
private:
    bool selectCar();
    void calculateCost();
    bool confirmCarAndCost();
    bool makePayment();
    void updateDb();
public:
    CarType carType;
    int numbPersons = 0;
    Location startLocation;
    Location endLocation;
    
    Car selectedCar;
    int cost = 0;
    
    
    
    RentRequest() = default;
    static RentRequest getFromTerminal();
    void run();
};

#endif // RENTREQUEST_H
