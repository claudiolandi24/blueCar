#include "menulogin.h"
#include "menuadmin.h"
#include "menuuser.h"
#include <iostream>

void ActionLogin::run() {
	cout << "Insert your username" << endl;
	string userName;
	cin >> userName;
	printEmptyLineSeparator();

	if (userName == "admin") {
		MenuAdmin ma("");
		ma.run();
	} else if (userName == "claudio") {
		MenuUser mu("");
		mu.run();
	} else {
		cout << "Invalid user " << userName << endl;
	}

	printEmptyLineSeparator();
};

void ActionRegister::run() {
	cout << "running register" << endl;
	printEmptyLineSeparator();
};

MenuLogin::MenuLogin(string label_)
    : Menu(label_) {
	title = "LOGIN";
	addItem(make_unique<ActionLogin>("Log in (I already have an account)"));
	addItem(make_unique<ActionRegister>("Register (I do not have an account)"));
	exitLabel = "Quit";
}

void runApplication() {
	MenuLogin ml("");
	ml.run();
}
