#include "user.h"
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
    //TODO here
}

void User::setNameFromTerminal() { //TODO
}

void User::setSurnameFromTerminal() { //TODO
}

void User::setAddressFromTerminal() { //TODO
}

void User::setCreditCardFromTerminal() { //TODO
}

void User::setDrivingLicenseFromTerminal() { //TODO
}
