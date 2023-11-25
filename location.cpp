#include "location.h"
#include "rbk/QStacker/qstacker.h"

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

QMap<int, Location> Location::id_Location_Map() {
	static auto         locationList = getAllLocationsFromDb();
	QMap<int, Location> map;
	for (const auto& location : locationList) {
		map[location.id] = location;
	}
	return map;
}

//tolerant
int Location::getLocationIdTolerant(QString location) {
    location = location.trimmed();
    location = location.toLower();
    
    // Initial letter -> full name
    QMap<QChar, QString> initial_location;
    initial_location['i']="inner circle";
    initial_location['m']="middle circle";
    initial_location['o']="outer circle";
    if(location.size()==1 and initial_location.contains(location[0])){
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
		qCritical().noquote() << "wrong location id" << QStacker16Light();
		return "";
	}
	return map[id].name;
}
