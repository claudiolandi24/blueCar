#ifndef RENTREQUEST_H
#define RENTREQUEST_H

#include "car.h"
#include "cartype.h"
#include "location.h"
#include "user.h"

class RentRequest
{
private:
    bool selectCar();
    bool confirmCarAndCost();
    bool makePayment();
    bool confirmAndMakePayment();
    void updateDb();
public:
    User* user;
    CarType carType;
    int numbPersons = 0;
    Location startLocation;
    Location endLocation;
    // km
    int distance = 0;
    
    Car car;
    int cost = 0;
    
    
    
    RentRequest() = default;
    static RentRequest getFromTerminal();
    void run();
};

#endif // RENTREQUEST_H
