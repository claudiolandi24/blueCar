#include "location.h"

extern DB db;

Location Location::fromSqlRow(const sqlRow& row) {
	Location location;
	row.get2("id", location.id);
	row.get2("name", location.name);
	return location;
}

QList<Location> Location::getAllLocationsFromDb() {
	auto            sql = QSL("SELECT * FROM location;");
	auto            res = db.query(sql);
	QList<Location> locationList;
	for (const auto& row : res) {
		locationList.push_back(fromSqlRow(row));
	}
	return locationList;
}

int Location::getLocationId(QString location) {
	location = location.trimmed();
	location = location.toLower();
	if (location == "inner circle") {
		return 1;
	} else if (location == "middle circle") {
		return 2;
	} else if (location == "outer circle") {
		return 3;
	} else {
		return 0;
	}
}

QString Location::getLocationNameHuman(int id) {
	if (id == 1) {
		return "Inner Circle";
	} else if (id == 2) {
		return "Middle Circle";
	} else if (id == 3) {
		return "Outer Circle";
	} else
		return QString();
}
