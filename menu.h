#ifndef MENU_H
#define MENU_H

#include "menuitem.h"
#include <memory>
#include <string>
#include <vector>

using namespace std;

class ItemVector {
      private:
	vector<unique_ptr<MenuItem>> items;

      public:
	/*
	 * Must be:
	 * 1 <= itemNumber <= this->size()
	 *
	 * I.e., indexing starts from 1, so that "itemNumber" is the same as the number linked to the
	 * item when the menu is printed (in Menu::show())
	 */
	unique_ptr<MenuItem>& getItemByItemNumber(unsigned long itemNumber) {
		//TODO check range valid
		unsigned long index = itemNumber - 1;
		return items[index];
	}
	void push_back(unique_ptr<MenuItem>& item) {
		items.push_back(move(item));
	}
	unsigned long size() {
		return items.size();
	}
};

class Menu : public MenuItem {
      protected:
	string     title;
	ItemVector items;
	string     exitLabel = "Back";

	void addItem(unique_ptr<MenuItem> item);
	void show();
	int  askForOption();

      public:
	Menu(string label_)
	    : MenuItem(label_){};
	void run() override;
};

#endif // MENU_H
