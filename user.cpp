#include "user.h"
#include "creditcard.h"
#include "hash.h"
#include "menuupdateuser.h"
#include "rbk/minMysql/min_mysql.h"
#include "rbk/misc/b64.h"
#include "validate.h"
#include "variadictable.h"

extern DB db;

User::User() {
	entityName = "user";
	table      = "user";
}

User User::getNewUserFromTerminal() {
	User user;
	user.setUsernameFromTerminal();
	user.setPwdHashFromTerminal();
	user.setNameFromTerminal();
	user.setSurnameFromTerminal();
	user.setAddressFromTerminal();
	user.setCreditCardFromTerminal();
	user.setDrivingLicenseFromTerminal();

	return user;
}

User User::getUserFromSqlRow(const sqlRow& row) {
	User user;
	row.get2("id", user.id);
	row.get2("username", user.username);
	row.get2("pwdHash", user.pwdHash);
	row.get2("name", user.name);
	row.get2("surname", user.surname);
	row.get2("address", user.address);

	long long creditCardId = 0;
	row.get2("creditCardId", creditCardId);
	auto cardList   = CreditCard::getCreditCardsFromDb(QSL("where id = %1").arg(creditCardId));
	user.creditCard = cardList[0];

	row.get2("drivingLicense", user.drivingLicense);

	return user;
}

void User::saveToDb() {
	creditCard.saveToDb();
	QString skel = R"(
INSERT INTO user
SET username = %1,
    pwdHash = '%2',
    name = %3,
    surname = %4,
    address = %5,
    creditCardId = %6,
    drivingLicense = %7;
)";
	auto    sql  = skel
	               .arg(base64this(username))
	               .arg(pwdHash)
	               .arg(base64this(name))
	               .arg(base64this(surname))
	               .arg(base64this(address))
	               .arg(creditCard.id)
	               .arg(base64this(drivingLicense));
	db.query(sql);
}

//TODO IMP
// check all these validations
// check ones in car
// credit card
// others? -> all validations
void User::setUsernameFromTerminal() {
	username = getValidatedString("Choose an username and insert it", make_unique<ValidateGeneralAlphaNum>());
}

void User::setPwdHashFromTerminal() {
	QString pwd = getValidatedString("Choose a password and insert it", make_unique<ValidatePwd>());
	pwdHash     = getHash(pwd);
}

void User::setNameFromTerminal() {
	name = getValidatedString("Insert the name", make_unique<ValidateGeneralAlphaNum>());
}

void User::setSurnameFromTerminal() {
	surname = getValidatedString("Insert the surname", make_unique<ValidateGeneralAlphaNum>());
}

void User::setAddressFromTerminal() {
	address = getValidatedString("Insert the address", make_unique<ValidateGeneralAlphaNum>());
}

void User::setCreditCardFromTerminal() {
	creditCard = CreditCard::getNewCreditCardFromTerminal();
}

void User::setDrivingLicenseFromTerminal() {
	drivingLicense = getValidatedString("Insert the driving license", make_unique<ValidateDrivingLicense>());
}

QList<User> User::getUsersFromDb(const QString& whereCondition) {
	auto skel = QSL("select * from user %1;");
	auto sql  = skel.arg(whereCondition);
	auto res  = db.query(sql);

	QList<User> users;
	for (const auto& row : res) {
		users.push_back(getUserFromSqlRow(row));
	}
	return users;
}

void User::printAllUsersAsTable() {
	auto users = getUsersFromDb();
	printUsersAsTable(users);
}

void User::printUsersAsTable(const QList<User>& users) {
	VariadicTable<long long, string, string, string, string, string> table({"Id",
	                                                                        "Username",
	                                                                        "Name",
	                                                                        "Surname",
	                                                                        "Address",
	                                                                        "Driving License"},
	                                                                       10);
	for (const auto& u : users) {
		table.addRow(u.id,
		             u.username.toStdString(),
		             u.name.toStdString(),
		             u.surname.toStdString(),
		             u.address.toStdString(),
		             u.drivingLicense.toStdString());
	}
	table.print(std::cout);
}

void User::printAsTable() {
	printUsersAsTable({*this});
}

void User::updateUserAfterRequest() {
	auto userId = getIdFromTerminal("update");
	if (!userId.first) {
		QTextStream(stdout) << "Update operation canceled" << Qt::endl;
		return;
	}

	auto userList = getUsersFromDb(QSL("where id = %1").arg(userId.second));
	User user     = userList[0];
	QTextStream(stdout) << "Updating user:" << Qt::endl;

	user.printAsTable();

	MenuUpdateUser menuUpdate("", &user);
	menuUpdate.run();
}

void User::updateInDb() {
	creditCard.updateInDb();

	QString skel = R"(
UPDATE user SET
    username = %1,	
    pwdHash = '%2',	
    name = %3,	
    surname = %4,	
    address = %5,	
    drivingLicense = %6
WHERE id = %7;
)";
	auto    sql  = skel
	               .arg(base64this(username))
	               .arg(pwdHash)
	               .arg(base64this(name))
	               .arg(base64this(surname))
	               .arg(base64this(address))
	               .arg(base64this(drivingLicense))
	               .arg(id);
	db.query(sql);
}
