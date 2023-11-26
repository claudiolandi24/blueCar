#include "service.h"
#include "config.h"
#include "rbk/minMysql/min_mysql.h"
#include "utilityfunctions.h"
#include <QDate>

extern DB db;

void Service::scheduleService(const Car& car) {
	Service service;
	service.carId = car.id;
	// We suppose it is always possible to do  a service tomorrow
	service.date                  = QDateTime::currentDateTimeUtc().date().addDays(1);
	service.totalDistanceTraveled = car.totalDistanceTraveled;
	service.cost                  = config::serviceCost;
    
    service.saveInDb();
}

void Service::saveInDb() {
	QString skel = R"(
INSERT INTO service
SET
carId = %1,
date = %2,
totalDistanceTraveled = %3,
cost = %4; 
)";
	auto    sql  = skel
	               .arg(carId)
	               .arg(getMysqlString(date))
	               .arg(totalDistanceTraveled)
	               .arg(cost);
	db.query(sql);
	id = int(db.lastId());
}
