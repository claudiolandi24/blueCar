#ifndef RENTEDCARVIEW_H
#define RENTEDCARVIEW_H

#include "rentrequest.h"

// Existimated
int     getWaitingTime(const RentRequest& request);
QDate   getNextServiceDate(int carId);
QString getNextServiceDateString(int carId);

#endif // RENTEDCARVIEW_H
