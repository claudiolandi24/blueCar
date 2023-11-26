#include "rent.h"
#include "rbk/defines/stringDefine.h"
#include "rbk/minMysql/min_mysql.h"

extern DB db;

void Rent::saveInDb() {
	QString skel = R"(
INSERT INTO rent
SET userId = %1
    carId = %2,
    startLocationId = %3,
    startDateTime = %4,
    endLocationId = %5,
    endDateTime = NULL,
    estimatedEndDateTime = %6,
    distance = %7, 
    cost = %8;
)";
	auto    sql  = skel
	               .arg(userId)
	               .arg(carId)
	               .arg(startLocationId)
	               .arg(startDateTime.toString(mysqlDateTimeFormat))
	               .arg(endLocationId)
	               .arg(estimatedEndDateTime.toString(mysqlDateTimeFormat))
	               .arg(distance)
	               .arg(cost);
    db.query(sql);
}


