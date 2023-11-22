#include "menulogin.h"
#include "menuadmin.h"
#include "menuuser.h"
#include <iostream>
#include <QTextStream>

void ActionLogin::run() {
	cout << "Insert your username" << endl;
    QString userName = QTextStream(stdin).readLine();
	//string userName;
	//cin >> userName;
	printEmptyLineSeparator();

	if (userName == "admin") {
		MenuAdmin ma("");
		ma.run();
	} else if (userName == "claudio") {
		MenuUser mu("");
		mu.run();
	} else {
        //TODO remove all cout <<. use qtextstream. so here remove toStdString()
		cout << "Invalid user " << userName.toStdString() << endl;
	}

	printEmptyLineSeparator(); };

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
