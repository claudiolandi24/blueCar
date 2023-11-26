#include "location.h"
#include "config.h"
#include "rbk/QStacker/qstacker.h"
#include <cassert>
#include <cstdlib>

extern DB db;

Location Location::fromSqlRow(const sqlRow& row) {
	Location location;
	row.get2("id", location.id);
	row.get2("name", location.name);
	return location;
}

Location Location::fromId(int id) {
	static auto map = id_Location_Map();
	if (!map.contains(id)) {
		qCritical().noquote() << "wrong location id" << QStacker16Light();
	}
	return map[id];
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

bool Location::operator==(const Location& location2) const {
	assert(id);
	assert(location2.id);
	assert(!name.isEmpty());
	assert(!location2.name.isEmpty());
	return id == location2.id and name == location2.name;
}

QMap<int, Location> Location::id_Location_Map() {
	static auto         locationList = getAllLocationsFromDb();
	QMap<int, Location> map;
	for (const auto& location : locationList) {
		map[location.id] = location;
	}
	return map;
}

int Location::getLocationIdTolerant(QString location) {
	location = location.trimmed();
	location = location.toLower();

	// Initial letter -> full name
	QMap<QChar, QString> initial_location;
	initial_location['i'] = "inner circle";
	initial_location['m'] = "middle circle";
	initial_location['o'] = "outer circle";
	if (location.size() == 1 and initial_location.contains(location[0])) {
		location = initial_location[location[0]];
	}
	return getLocationId(location);
}

/*
 * Case-insensitive
 */
int Location::getLocationId(QString name) {
	static auto locationList = getAllLocationsFromDb();
	for (const auto& location : locationList) {
		if (location.name.toLower() == name.toLower()) {
			return location.id;
		}
	}
	return 0;
}

QString Location::getLocationNameHuman(int id) {
	static auto map = id_Location_Map();
	if (!map.contains(id)) {
		qCritical().noquote() << "wrong location id = " << id << "\n"
		                      << QStacker16Light();
		return "";
	}
	return map[id].name;
}

QChar Location::initial() const {
	return name[0].toUpper();
}

int Location::distanceFromInner() const {
	if (initial() == 'I') {
		return 0;
	}
	if (initial() == 'M') {
		return 1;
	}
	if (initial() == 'O') {
		return 2;
	}
	qCritical().noquote() << "wrong location initial" << QStacker16Light();
	return -1;
}

int getDistanceInHops(const Location& loc1, const Location& loc2) {
	int distance = abs(loc1.distanceFromInner() - loc2.distanceFromInner()) + 1;
	return distance;
}

int getDistanceInKm(const Location& loc1, const Location& loc2) {
	return getDistanceInHops(loc1, loc2) * config::kmPerHop;
}
