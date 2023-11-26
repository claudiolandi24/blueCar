#ifndef CONFIG_H
#define CONFIG_H

#include "rbk/minMysql/DBConf.h"
#include <QString>

namespace config {
extern QString mariaDbHost;
extern QString mariaDbUser;
extern QString mariaDbPwd;
extern int     mariaDbPort;
extern QString mariaDbDefaultDb;

extern QString adminPwdHash;
extern int     kmPerHop;
extern bool    paymentOperationSuccess;
extern int     serviceEveryKm;
// $ cent
extern int serviceCost;

} // namespace config

#endif // CONFIG_H
