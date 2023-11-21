#include "menu.h"
#include <iostream>

using namespace std;

MenuItem::MenuItem(string label_) {
	label = label_;
}

void MenuItem::printEmptyLineSeparator() {
	cout << "\n\n";
}

void Menu::show() {
	cout << "--- " << title << " ---" << endl;
	for (unsigned i = 0; i < items.size(); i++) {
		cout << "-" << i + 1 << " " << items[i]->label << endl;
	}
	cout << "-0 " << exitLabel << endl;
}

int Menu::askForOption() {
	cout << "Select an option" << endl;
	//TODO remove everywhere unsigned
	unsigned option;
	cin >> option;
	printEmptyLineSeparator();
	return int(option);
}

void Menu::run() {
	while (true) {
		show();
		int selectedOption = askForOption();
		if (!selectedOption) {
			break;
		}
		items[unsigned(selectedOption - 1)]->run();
	}
};

void Menu::addItem(unique_ptr<MenuItem> item) {
	items.push_back(move(item));
}

MenuLogin::MenuLogin(string label_)
    : Menu(label_) {
	title = "LOGIN";
	addItem(make_unique<ActionLogin>("Log in\n(I already have an account.)"));
	addItem(make_unique<ActionRegister>("Register\n(I do not have an account.)"));
	exitLabel = "Quit";
}

MenuAdmin::MenuAdmin(string label_)
    : Menu(label_) {
	title = "ADMIN";
	addItem(make_unique<MenuManageCar>("Manage cars"));
	addItem(make_unique<MenuManageUser>("Manage users"));
	exitLabel = "Log out";
}

MenuManageCar::MenuManageCar(string label_)
    : Menu(label_) {
	title = "MANAGE CAR";
	addItem(make_unique<ActionAddCar>("Add car"));
	addItem(make_unique<ActionUpdateCar>("Update car"));
	addItem(make_unique<ActionRemoveCar>("Remove car"));
	addItem(make_unique<ActionShowCars>("Show cars"));
}

MenuManageUser::MenuManageUser(string label_)
    : Menu(label_) {
	title = "MANAGE USER";
	addItem(make_unique<ActionAddUser>("Add user"));
	addItem(make_unique<ActionUpdateUser>("Update user"));
	addItem(make_unique<ActionRemoveUser>("Remove user"));
	addItem(make_unique<ActionShowUsers>("Show users"));
}

void ActionLogin::run() {
	MenuAdmin ma("");
	ma.run();

	printEmptyLineSeparator();
};

void ActionRegister::run() {
	cout << "running register" << endl;
	printEmptyLineSeparator();
};

void ActionAddCar::run() {
	cout << "running add car" << endl;
	printEmptyLineSeparator();
};
void ActionUpdateCar::run() {
	cout << "running update car" << endl;
	printEmptyLineSeparator();
};
void ActionRemoveCar::run() {
	cout << "running remove car" << endl;
	printEmptyLineSeparator();
};
void ActionShowCars::run() {
	cout << "running show cars" << endl;
	printEmptyLineSeparator();
};

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

void tryMenu() {
	MenuLogin ml("");
	ml.run();
}
