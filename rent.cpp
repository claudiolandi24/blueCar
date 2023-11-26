#include "rent.h"
#include "rbk/defines/stringDefine.h"
#include "rbk/minMysql/min_mysql.h"
#include "rbk/misc/b64.h"
#include "utilityfunctions.h"

extern DB db;

void Rent::saveInDb() {
	QString skel = R"(
INSERT INTO rent
SET userId = %1,
    carId = %2,
    startLocationId = %3,
    startDateTime = %4,
    endLocationId = %5,
    endDateTime = %6,
    estimatedEndDateTime = %7,
    distance = %8, 
    cost = %9;
)";
	auto    sql  = skel
	               .arg(userId)
	               .arg(carId)
	               .arg(startLocationId)
	               .arg(getMysqlString(startDateTime))
	               .arg(endLocationId)
	               .arg(getMysqlString(endDateTime))
	               .arg(getMysqlString(estimatedEndDateTime))
	               .arg(distance)
	               .arg(cost);
	db.query(sql);
	id = (long long)(db.lastId());
}
