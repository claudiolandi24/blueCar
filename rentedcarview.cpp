#include "rentedcarview.h"
#include "rbk/minMysql/min_mysql.h"

extern DB db;

// seconds
int getWaitingTime(const RentRequest& request) {
	QString skel = R"(
select *
from rentedCarView
where carTypeId = %1
  and endLocationId = %2
order by estimatedEndDateTime asc
limit 1;
)";
	auto    sql  = skel
	               .arg(request.carType.id)
	               .arg(request.startLocation.id);
	auto res = db.query(sql);
	if (!res.isEmpty()) {
		auto endTimeStr = res[0]["estimatedEndDateTime"];
		auto endTime    = QDateTime::fromString(endTimeStr, mysqlDateTimeFormat);

		auto now         = QDateTime::currentDateTimeUtc();
		auto waitingTime = now.secsTo(endTime);
		return int(waitingTime);
	}
	return -1;
}

QDate getNextServiceDate(int carId) {
	QString skel = R"(
select *
from lastServiceView
where carId = %1;
)";
	auto    sql  = skel.arg(carId);
	auto    res  = db.query(sql);
	if (res.isEmpty()) {
		return {};
	}
	auto serviceDateStr = res[0]["serviceDate"];
	auto serviceDate    = QDate::fromString(serviceDateStr, mysqlDateFormat);
	auto today          = QDateTime::currentDateTimeUtc().date();
	if (serviceDate >= today) {
		// we want only a scheduled service, it must be in future
		return serviceDate;
	}
	return {};
}

QString getNextServiceDateString(int carId) {
	auto serviceDate = getNextServiceDate(carId);
	if (serviceDate.isNull()) {
		return "not scheduled";
	}
	return serviceDate.toString(mysqlDateFormat);
}
