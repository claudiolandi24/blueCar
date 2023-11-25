#ifndef CARTYPE_H
#define CARTYPE_H

#include "rbk/minMysql/min_mysql.h"
#include <QString>

class CarType {
      public:
	int     id = 0;
	QString name;
	int     numbPersons = 0;
	// $cent / km
	int cost = 0;
	// km / h
	int speed = 0;

	CarType() = default;
	static CarType fromSqlRow(sqlRow row);
	static CarType fromId(int id);

	static QList<CarType>     getAllCarTypesFromDb();
	static QMap<QString, int> get_Name_Id_Map();
	static QMap<int, CarType> get_id_CarType_Map();
	static int                getIdFromName(const QString& type);
	static int                getIdFromNameTolerant(QString type);
	static QString            getTypeNameHuman(int id);
};

#endif // CARTYPE_H
