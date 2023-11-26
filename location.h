#ifndef LOCATION_H
#define LOCATION_H

#include "rbk/minMysql/min_mysql.h"
#include <QList>
#include <QString>

class Location {
      public:
	int     id = 0;
	QString name;

	Location() = default;
	static Location        fromSqlRow(const sqlRow& row);
	static Location        fromId(int id);
	static QList<Location> getAllLocationsFromDb();
    bool operator==(const Location& location2) const;

	static QMap<int, Location> id_Location_Map();

	static int     getLocationIdTolerant(QString location);
	static int     getLocationId(QString name);
	static QString getLocationNameHuman(int id);
};

#endif // LOCATION_H
