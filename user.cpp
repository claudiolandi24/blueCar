#include "user.h"
#include "hash.h"
#include "validate.h"

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
	//TODO
}

void User::setUsernameFromTerminal() {
	username = getValidatedString("Choose an username and insert it", make_unique<ValidateGeneralAlphaNum>());
}

void User::setPwdHashFromTerminal() {
	QString pwd = getValidatedString("Choose a password and insert it", make_unique<ValidatePwd>());
	pwdHash     = hash0(pwd);
}

void User::setNameFromTerminal() {
	name = getValidatedString("Insert the name of the user", make_unique<ValidateGeneralAlphaNum>());
}

void User::setSurnameFromTerminal() {
	surname = getValidatedString("Insert the surname of the user", make_unique<ValidateGeneralAlphaNum>());
}

void User::setAddressFromTerminal() { //TODO
    //here
}

void User::setCreditCardFromTerminal() { //TODO
}

void User::setDrivingLicenseFromTerminal() {
	drivingLicense = getValidatedString("Insert the driving license of the user", make_unique<ValidateDrivingLicense>());
}
