#include "menuupdateuser.h"

void ActionUpdateUser::updateInDb() {
	user->updateInDb();
	QTextStream(stdout) << "User updated successfully:" << Qt::endl;
	user->printAsTable();
	printEmptyLineSeparator();
}

void ActionUpdateUsername::run() {
	user->setUsernameFromTerminal();
	updateInDb();
}

void ActionUpdatePwdHash::run() {
	user->setPwdHashFromTerminal();
	updateInDb();
}

void ActionUpdateNameOfUser::run() {
	user->setNameFromTerminal();
	updateInDb();
}

void ActionUpdateSurname::run() {
	user->setSurnameFromTerminal();
	updateInDb();
}

void ActionUpdateAddress::run() {
	user->setAddressFromTerminal();
	updateInDb();
}

void ActionUpdateCreditCard::run() {
	user->setCreditCardFromTerminal();
	updateInDb();
}

void ActionUpdateDrivingLicense::run() {
	user->setDrivingLicenseFromTerminal();
	updateInDb();
}

MenuUpdateUser::MenuUpdateUser(string label_, User* user_)
    : Menu(label_) {
	user = user_;

	title = "UPDATE USER";
	addItem(make_unique<ActionUpdateUsername>("Update the username", user));
	addItem(make_unique<ActionUpdatePwdHash>("Update the password", user));
	addItem(make_unique<ActionUpdateNameOfUser>("Update the name", user));
	addItem(make_unique<ActionUpdateSurname>("Update the surname", user));
	addItem(make_unique<ActionUpdateAddress>("Update the address", user));
	addItem(make_unique<ActionUpdateCreditCard>("Update the credit card", user));
	addItem(make_unique<ActionUpdateDrivingLicense>("Update the driving license", user));
	exitLabel = "End the update operation";
}
