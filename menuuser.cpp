#include "menuuser.h"
#include "user.h"
#include "utilityfunctions.h"
#include <QTextStream>
#include <iostream>

void ActionRentCar::run() {
	cout << "running rent car" << endl;
	printEmptyLineSeparator();
};

void ActionUnsubscribe::run() {
	cout << "--- UNSUBSCRIBE ---" << endl;
	QTextStream(stdout) << "Are you sure you want to unsubscribe? Press 'yes' to unsubscribe or 'no' to keep your account (Y/N)\n";
	if (yesFromTerminal()) {
		User::setNotActiveInDb(loggedUserId);
		QTextStream(stdout) << "Unsubscribe operation completed successfully\n";
	} else {
		QTextStream(stdout) << "Unsubscribe operation canceled\n";
	}

	printEmptyLineSeparator();
};

MenuUser::MenuUser(string label_, long long loggedUserId_)
    : Menu(label_) {
	loggedUserId = loggedUserId_;

	title = "USER";
	addItem(make_unique<ActionRentCar>("Rent car"));
	addItem(make_unique<ActionUnsubscribe>("Unsubscribe", loggedUserId));
	exitLabel = "Log out";
}
