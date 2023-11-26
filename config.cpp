#include "config.h"

namespace config {
// IMPORTANT
QString mariaDbHost = "127.0.0.1";
QString mariaDbUser = "claudio";
QString mariaDbPwd  = "claudio";
int     mariaDbPort = 3306;

// can leave the deafult
QString mariaDbDefaultDb        = "blueCar";
int     kmPerHop                = 5;
bool    paymentOperationSuccess = true;
int     serviceEveryKm          = 1500;
int     serviceCost             = 30000;

// to have pwd of admin = "admin" (while debugging or testing)

// use this combination
bool    simulateHash = true;
QString adminPwdHash = "HASH_OF_admin";


// OR use this combination
/*bool    simulateHash = false;
QString adminPwdHash = "5a38afb1a18d408e6cd367f9db91e2ab9bce834cdad3da24183cc174956c20ce35dd39c2bd36aae907111ae3d6ada353f7697a5f1a8fc567aae9e4ca41a9d19d";
*/

} // namespace config
