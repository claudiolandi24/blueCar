#include "menu.h"
#include <iostream>

using namespace std;

MenuItem::MenuItem(string label_) {
	label = label_;
}

MenuItem::~MenuItem() {
}

Menu::~Menu() {
	for (auto itr = items.begin(); itr != items.end(); itr++) {
		delete *itr;
	}
}

void Menu::show() {
	cout << "--- " << title << " ---" << endl;
	for (unsigned i = 0; i < items.size(); i++) {
		cout << "-" << i << " " << items[i]->label << endl;
	}
	cout << "---" << endl;
}

void Menu::runSelectedItem() {
	cout << "Select an option" << endl;
	unsigned option;
	cin >> option;
	items[option]->run();
}

void Menu::run() {
	show();
	runSelectedItem();
};

void Menu::addItem(MenuItem* item) {
	items.push_back(item);
}

MenuLogin::MenuLogin(string label_)
    : Menu(label_) {
	title = "LOGIN";
	addItem(new Action1("Action 1"));
	addItem(new Action2("Action 2"));
}

Action::~Action() {
}

void Action::run(){

};

Action1::~Action1() {
}

void Action1::run() {
	cout << "running action 1" << endl;
};

Action2::~Action2() {
}

void Action2::run() {
	cout << "running action 2" << endl;
};

void tryMenu() {
	MenuLogin ml("");
	ml.run();
}
