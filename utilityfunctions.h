#ifndef UTILITYFUNCTIONS_H
#define UTILITYFUNCTIONS_H

#include <QPair>
#include <QString>
#include <memory>

using namespace std;





int     getTypeId(QString type);
QString getTypeNameHuman(int id);
int     getLocationId(QString location);
QString getLocationNameHuman(int id);
QString getAvailabilityHuman(bool isFree);
bool    isAlphanumeric(const QString& string);
bool    isAlphanumeric(const QString& string, int maxLen);

#endif // UTILITYFUNCTIONS_H
