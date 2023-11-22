#include "menumanageuser.h"
#include <iostream>

void ActionAddUser::run() {
	cout << "running add user" << endl;
	printEmptyLineSeparator();
};

void ActionUpdateUser::run() {
	cout << "running update user" << endl;
	printEmptyLineSeparator();
};

void ActionRemoveUser::run() {
	cout << "running remove user" << endl;
	printEmptyLineSeparator();
};

void ActionShowUsers::run() {
	cout << "running show users" << endl;
	printEmptyLineSeparator();
};

MenuManageUser::MenuManageUser(string label_)
    : Menu(label_) {
	title = "MANAGE USERS";
	addItem(make_unique<ActionAddUser>("Add user"));
	addItem(make_unique<ActionUpdateUser>("Update user"));
	addItem(make_unique<ActionRemoveUser>("Remove user"));
	addItem(make_unique<ActionShowUsers>("Show users"));
}
