#ifndef USER_H
#define USER_H

#include "creditcard.h"
#include "entity.h"
#include "rbk/minMysql/min_mysql.h"
#include <QString>

class User : public Entity {
      public:
	long long  id = 0;
	QString    username;
	QString    pwdHash;
	QString    name;
	QString    surname;
	QString    address;
	CreditCard creditCard;
	QString    drivingLicense;

	User();
	static User        getNewUserFromTerminal();
	static User        getUserFromSqlRow(const sqlRow& row);
	static QList<User> getUsersFromDb(const QString& whereCondition = "");
	void               saveToDb();

	void setUsernameFromTerminal();
	void setPwdHashFromTerminal();
	void setNameFromTerminal();
	void setSurnameFromTerminal();
	void setAddressFromTerminal();
	void setCreditCardFromTerminal();
	void setDrivingLicenseFromTerminal();

	static void printAllUsersAsTable();
	static void printUsersAsTable(const QList<User>& users);
	void        printAsTable();

	static void updateUserAfterRequest();
	void        updateInDb();
};

#endif // USER_H
