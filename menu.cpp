#include "menu.h"
#include <iostream>

using namespace std;

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
