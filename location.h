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
	bool                   operator==(const Location& location2) const;

	static QMap<int, Location> id_Location_Map();

	static int     getLocationIdTolerant(QString location);
	static int     getLocationId(QString name);
	static QString getLocationNameHuman(int id);
	/*
	 * Return initial letter of the name: I, M or O
	 */
	QChar initial() const;
    /*
     * Return distance from Inner Circle NOT in hops
     */ 
	int   distanceFromInner() const;
};

int getDistanceInHops(const Location& loc1, const Location& loc2);
int getDistanceInKm(const Location& loc1, const Location& loc2);

#endif // LOCATION_H
