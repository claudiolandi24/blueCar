#ifndef SERVICE_H
#define SERVICE_H

#include "car.h"
#include <QDate>

class Service
{
public:
    int id = 0;
    int carId = 0;
    QDate date;
    // km
    int totalDistanceTraveled = 0;
    // $ cent
    int cost = 0;
    
    Service()=default;
    static void scheduleService(const Car& car);
    void saveInDb();
};

#endif // SERVICE_H
