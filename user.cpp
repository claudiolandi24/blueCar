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
    username = getValidatedString("Insert the username", make_unique<ValidateGeneralAlphaNum>());
}

void User::setPwdHashFromTerminal() { //TODO
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
