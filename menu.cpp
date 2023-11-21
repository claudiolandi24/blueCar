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
	addItem(make_unique<ActionLogin>("I already have an account. Log in"));
	addItem(make_unique<ActionRegister>("I do not have an account. Register"));
	exitLabel = "Quit";
}

MenuAdmin::MenuAdmin(string label_)
    : Menu(label_) {
	title = "ADMIN";
	// car user
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

void tryMenu() {
	MenuLogin ml("");
	ml.run();
}
