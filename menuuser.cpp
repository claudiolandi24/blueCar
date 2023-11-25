#include "menuuser.h"
#include "menuupdateuser.h"
#include "user.h"
#include "utilityfunctions.h"
#include <QTextStream>
#include <iostream>

void ActionRentCar::run() {
	cout << "--- RENT CAR ---" << endl;
    
    
	printEmptyLineSeparator();
};

void ActionUnsubscribe::run() {
	cout << "--- UNSUBSCRIBE ---" << endl;
	QTextStream(stdout) << "Are you sure you want to unsubscribe? Press 'yes' to unsubscribe or 'no' to keep your account (Y/N)\n";
	if (utility::yesFromTerminal()) {
		User::setNotActiveInDb(loggedUserId);
		QTextStream(stdout) << "Unsubscribe operation completed successfully\n";
	} else {
		QTextStream(stdout) << "Unsubscribe operation canceled\n";
	}

	printEmptyLineSeparator();
};

MenuUser::MenuUser(string label_, User *user_)
    : Menu(label_) {
	user = user_;

	title = "USER";
	addItem(make_unique<ActionRentCar>("Rent car"));
	addItem(make_unique<ActionUnsubscribe>("Unsubscribe", user->id));
    addItem(make_unique<MenuUpdateUser>("Update my data",user));
	exitLabel = "Log out";
}
