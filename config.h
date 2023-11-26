#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

namespace config {
extern QString adminPwdHash;
extern int     kmPerHop;
extern bool    paymentOperationSuccess;
extern int     serviceEveryKm;
// $ cent
extern int serviceCost;

bool readConfigFile();
} // namespace config

#endif // CONFIG_H
