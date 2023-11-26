#include "menulogin.h"
#include "config.h"
#include "hash.h"
#include "menuadmin.h"
#include "menumanageuser.h"
#include "menuuser.h"
#include "utilityfunctions.h"
#include <QTextStream>
#include <cassert>
#include <iostream>

QPair<bool, User> ActionLogin::checkPwd(const QString& username, const QString& password) {
	if (username == "admin") {
		// admin
		if (getHash(password) != config::adminPwdHash) {
			return {false, {}};
		}
		return {true, {}};
	} else {
		// normal user
		bool ok = User::usernameExists(username) and getHash(password) == User::getPwdHash(username);
		if (!ok) {
			return {false, {}};
		} else {
			return {true, User::getByUsername(username)};
		}
	}
}

void ActionLogin::run() {
	QTextStream(stdout) << "--- LOGIN ---" << Qt::endl;
	QTextStream(stdout) << "Insert your username" << Qt::endl;
	QString username = QTextStream(stdin).readLine();
	QTextStream(stdout) << "Insert your password\n";
	QString pwd = QTextStream(stdin).readLine();

	printEmptyLineSeparator();

	auto check = checkPwd(username, pwd);
	if (!check.first) {
		QTextStream(stdout) << "Invalid username or password\n";
	} else if (username == "admin") {
		MenuAdmin menuAdmin("");
		menuAdmin.run();
	} else {
        auto user = User::getById(check.second.id);
		MenuUser menuUser("",&user);
		menuUser.run();
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
	addItem(make_unique<ActionAddUser>("Register (I do not have an account)", Actor::NormalUser));
	exitLabel = "Quit";
}

void runApplication() {
	MenuLogin ml("");
	ml.run();
}
