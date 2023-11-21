#include "menu.h"
#include <iostream>

using namespace std;

MenuItem::MenuItem(string label_) {
	label = label_;
}

MenuItem::~MenuItem() {
}

void MenuItem::printEmptyLineSeparator() {
	cout << "\n\n";
}

Menu::~Menu() {
	for (auto itr = items.begin(); itr != items.end(); itr++) {
		delete *itr;
	}
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

void Menu::addItem(MenuItem* item) {
	items.push_back(item);
}

MenuLogin::MenuLogin(string label_)
    : Menu(label_) {
	title = "LOGIN";
	addItem(new Action1("Action 1"));
	addItem(new Action2("Action 2"));
	exitLabel = "Quit";
}

Action::~Action() {
}

void Action::run(){

};

Action1::~Action1() {
}

void Action1::run() {
	cout << "running action 1" << endl;
	printEmptyLineSeparator();
};

Action2::~Action2() {
}

void Action2::run() {
	cout << "running action 2" << endl;
	printEmptyLineSeparator();
};

void tryMenu() {
	MenuLogin ml("");
	ml.run();
}
