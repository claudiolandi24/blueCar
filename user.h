#ifndef USER_H
#define USER_H

#include "creditcard.h"
#include <QString>

class User {
      public:
	long long  id = 0;
	QString    username;
	QString    pwdHash;
	QString    name;
	QString    surname;
	QString    address;
	CreditCard creditCard;
	QString    drivingLicense;

	User() = default;
	static User getNewUserFromTerminal();
	void        saveToDb();

	void setUsernameFromTerminal();
	void setPwdHashFromTerminal();
	void setNameFromTerminal();
	void setSurnameFromTerminal();
	void setAddressFromTerminal();
	void setCreditCardFromTerminal();
	void setDrivingLicenseFromTerminal();
};

#endif // USER_H
