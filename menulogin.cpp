#include "menulogin.h"
#include "menuadmin.h"
#include "menumanageuser.h"
#include "menuuser.h"
#include <QTextStream>
#include <iostream>

void ActionLogin::run() {
	QTextStream(stdout) << "--- LOGIN ---" << Qt::endl;
	cout << "Insert your username" << endl;
	QString userName = QTextStream(stdin).readLine();
	printEmptyLineSeparator();

	if (userName == "admin") {
		MenuAdmin menuAdmin("");
		menuAdmin.run();
	} else if (userName == "claudio") {
		MenuUser menuUser("");
		menuUser.run();
	} else {
		//TODO remove all cout <<. use qtextstream. so here remove toStdString()
		cout << "Invalid user " << userName.toStdString() << endl;
	}

	printEmptyLineSeparator();
};

void ActionRegister::run() {
	cout << "running register" << endl;
	printEmptyLineSeparator();
};

MenuLogin::MenuLogin(string label_)
    : Menu(label_) {
	title = "LOGIN OR REGISTER";
	addItem(make_unique<ActionLogin>("Log in (I already have an account)"));
	addItem(make_unique<ActionAddUser>("Register (I do not have an account)",Actor::NormalUser));
	exitLabel = "Quit";
}

void runApplication() {
	MenuLogin ml("");
	ml.run();
}
