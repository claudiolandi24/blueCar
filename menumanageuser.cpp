#include "menumanageuser.h"
#include "rbk/QStacker/qstacker.h"
#include "user.h"
#include "utilityfunctions.h"
#include <QTextStream>
#include <iostream>

QString ActionAddUser::title() {
	QString title = "--- ";
	switch (actor) {
	case Actor::Admin:
		title += "ADD USER";
		break;
	case Actor::NormalUser:
		title += "REGISTER";
		break;
	default:
		qCritical().noquote() << "invalid actor" << QStacker16Light();
	}
	title += " ---";
	return title;
}

QString ActionAddUser::confirmationMsg() {
	switch (actor) {
	case Actor::Admin:
		return "User added successfully";
		break;
	case Actor::NormalUser:
		return "registration completed successfully";
		break;
	default:
		qCritical().noquote() << "invalid actor" << QStacker16Light();
	}
	return {};
}

void ActionAddUser::run() {
	QTextStream(stdout) << title() << Qt::endl;

	User user = User::getNewUserFromTerminal();
	user.saveToDb();
	QTextStream(stdout) << confirmationMsg() << Qt::endl;
	printEmptyLineSeparator();
};

void ActionUpdateUser::run() {
	cout << "--- UPDATE ---" << endl;
	User::updateUserAfterRequest();

	printEmptyLineSeparator();
};

void ActionRemoveUser::run() {
	cout << "--- REMOVE USER ---" << endl;
	User::deleteAfterRequest();

	printEmptyLineSeparator();
};

MenuManageUser::MenuManageUser(string label_)
    : Menu(label_) {
	title = "MANAGE USERS";
	addItem(make_unique<ActionAddUser>("Add user", Actor::Admin));
	addItem(make_unique<ActionUpdateUser>("Update user"));
	addItem(make_unique<ActionRemoveUser>("Remove user"));
}

void MenuManageUser::actionBeforeShow() {
	User::printAllUsersAsTable();
	cout << "\n";
}
