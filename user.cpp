#include "user.h"
#include "hash.h"
#include "rbk/minMysql/min_mysql.h"
#include "rbk/misc/b64.h"
#include "validate.h"

extern DB db;

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

void User::saveToDb() {
	creditCard.saveToDb();
	QString skel = R"(
INSERT INTO user
SET username = %1,
    pwdHash = %2,
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
