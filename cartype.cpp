#include "cartype.h"
#include <QList>
#include <QMap>

extern DB db;

CarType CarType::fromSqlRow(sqlRow row) {
	CarType carType;
	row.get2("id", carType.id);
	row.get2("name", carType.name);
	row.get2("mubPersons", carType.numbPersons);
	row.get2("cost", carType.cost);
	row.get2("speed", carType.speed);
	return carType;
}

QList<CarType> CarType::getAllCarTypesFromDb() {
	auto           sql = QSL("SELECT * FROM carType");
	auto           res = db.query(sql);
	QList<CarType> carTypeList;
	for (const auto& row : res) {
		carTypeList.push_back(CarType::fromSqlRow(row));
	}
	return carTypeList;
}

QMap<QString, int> CarType::get_Name_Id_Map() {
	static auto        carTypeList = getAllCarTypesFromDb();
	QMap<QString, int> map_Name_Id;
	for (const auto& carType : carTypeList) {
		map_Name_Id[carType.name] = carType.id;
	}
	return map_Name_Id;
}

QMap<int, QString> CarType::get_id_name_Map() {
	static auto        carTypeList = getAllCarTypesFromDb();
	QMap<int, QString> map_Id_Name;
	for (const auto& carType : carTypeList) {
		map_Id_Name[carType.id] = carType.name;
	}
	return map_Id_Name;
}

int CarType::getIdFromName(const QString& type) {
	static auto map_name_id = get_Name_Id_Map();
	if (map_name_id.contains(type)) {
		return 0;
	}
	return map_name_id[type];
}

/*
 * Tolerant:
 * E.g.
 * e, E, eco, ECO -> ECO
 */
int CarType::getIdFromNameTolerant(QString type) {
	type = type.trimmed();
	type = type.toLower();

	// initial letter -> full name
	QMap<QChar, QString> initial_name_map;
	initial_name_map['e'] = "eco";
	initial_name_map['m'] = "mid-class";
	initial_name_map['d'] = "deluxe";
	if (type.size() == 1 and initial_name_map.contains(type[0])) {
		type = initial_name_map[type[0]];
	}

	type   = type.toUpper();
	int id = getIdFromName(type);
	return id;
}

QString CarType::getTypeNameHuman(int id) {
	if (id == 1) {
		return "ECO";
	} else if (id == 2) {
		return "MID-CLASS";
	} else if (id == 3) {
		return "DELUXE";
	} else
		return QString();
}
