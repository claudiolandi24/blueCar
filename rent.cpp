#include "rent.h"
#include "rbk/defines/stringDefine.h"
#include "rbk/minMysql/min_mysql.h"

extern DB db;

void Rent::saveInDb() {
	QString skel           = R"(
INSERT INTO rent
SET userId = %1
    carId = %2,
    startLocationId = %3,
    startDateTime = %4,
    endLocationId = %5,
    endDateTime = %6,
    estimatedEndDateTime = %7,
    distance = %8, 
    cost = %9;
)";
	QString endDateTimeStr = "NULL";
	if (!endDateTime.isNull()) {
		endDateTimeStr = endDateTime.toString(mysqlDateTimeFormat);
	}
	auto sql = skel
	               .arg(userId)
	               .arg(carId)
	               .arg(startLocationId)
	               .arg(startDateTime.toString(mysqlDateTimeFormat))
	               .arg(endLocationId)
	               .arg(endDateTimeStr)
	               .arg(estimatedEndDateTime.toString(mysqlDateTimeFormat))
	               .arg(distance)
	               .arg(cost);
	db.query(sql);
    id = (long long)(db.lastId());
}
