#include "config.h"

namespace config {
// IMPORTANT
QString mariaDbHost = "127.0.0.1";
QString mariaDbUser = "claudio";
QString mariaDbPwd  = "claudio";
int     mariaDbPort = 3306;

// can leave the deafult
QString mariaDbDefaultDb        = "blueCar";
QString adminPwdHash            = "HASH_OF_admin";
int     kmPerHop                = 5;
bool    paymentOperationSuccess = true;
int     serviceEveryKm          = 1500;
int     serviceCost             = 30000;

} // namespace config
