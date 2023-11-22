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
	for (unsigned itemNumber = 1; itemNumber <= items.size(); itemNumber++) {
		cout << "-" << itemNumber << " " << items.getItemByItemNumber(itemNumber)->label << endl;
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
		items.getItemByItemNumber(unsigned(selectedOption))->run();
	}
};

void Menu::addItem(unique_ptr<MenuItem> item) {
	items.push_back(item);
}

MenuLogin::MenuLogin(string label_)
    : Menu(label_) {
	title = "LOGIN";
	addItem(make_unique<ActionLogin>("Log in (I already have an account)"));
	addItem(make_unique<ActionRegister>("Register (I do not have an account)"));
	exitLabel = "Quit";
}

MenuAdmin::MenuAdmin(string label_)
    : Menu(label_) {
	title = "ADMIN";
	addItem(make_unique<MenuManageCar>("Manage cars"));
	addItem(make_unique<MenuManageUser>("Manage users"));
	exitLabel = "Log out";
}

MenuUser::MenuUser(string label_)
    : Menu(label_) {
	title = "USER";
	addItem(make_unique<ActionRentCar>("Rent car"));
	exitLabel = "Log out";
}

MenuManageCar::MenuManageCar(string label_)
    : Menu(label_) {
	title = "MANAGE CARS";
	addItem(make_unique<ActionAddCar>("Add car"));
	addItem(make_unique<ActionUpdateCar>("Update car"));
	addItem(make_unique<ActionRemoveCar>("Remove car"));
	addItem(make_unique<ActionShowCars>("Show cars"));
}

MenuManageUser::MenuManageUser(string label_)
    : Menu(label_) {
	title = "MANAGE USERS";
	addItem(make_unique<ActionAddUser>("Add user"));
	addItem(make_unique<ActionUpdateUser>("Update user"));
	addItem(make_unique<ActionRemoveUser>("Remove user"));
	addItem(make_unique<ActionShowUsers>("Show users"));
}

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

void ActionRentCar::run() {
	cout << "running rent car" << endl;
	printEmptyLineSeparator();
};

void tryMenu() {
	MenuLogin ml("");
	ml.run();
}
