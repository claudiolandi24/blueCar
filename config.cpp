#include "config.h"

namespace config {

QString adminPwdHash            = "HASH_OF_admin";
int     kmPerHop                = 5;
bool    paymentOperationSuccess = true;
int     serviceEveryKm          = 1500;

bool readConfigFile() {
	//TODO
	// adminPwdHash=from file
	return false;
}
} // namespace config
