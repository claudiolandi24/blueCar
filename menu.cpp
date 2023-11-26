#include "menu.h"
#include "utilityfunctions.h"
#include <QTextStream>
#include <iostream>

using namespace std;

void Menu::show() {
	cout << "--- " << title << " ---" << endl;
	actionBeforeShow();
	for (unsigned itemNumber = 1; itemNumber <= items.size(); itemNumber++) {
		cout << "-" << itemNumber << " " << items.getItemByItemNumber(itemNumber)->label << endl;
	}
	cout << "-0 " << exitLabel << endl;
}

int Menu::askForOption() {
	cout << "Select an option" << endl;
	QString strOption = QTextStream(stdin).readLine();
	bool    ok;
	int     option = strOption.toInt(&ok);
	if (!ok) {
		cout << "Invalid option " << strOption.toStdString() << "\n";
		return -1;
	}

	printEmptyLineSeparator();
	return option;
}

void Menu::run() {
	while (true) {
		show();
		int selectedOption = askForOption();
		if (!selectedOption) {
			// 0 -> end execution of this menu
			break;
		}
		if (selectedOption == -1) {
			// Invalid, do nothing
			printEmptyLineSeparator();
		} else {
			// Run selected option
			items.getItemByItemNumber(unsigned(selectedOption))->run();
		}
	}
};

void Menu::addItem(unique_ptr<MenuItem> item) {
	items.push_back(item);
}
