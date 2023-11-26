#include "rentedcarview.h"
#include "rbk/minMysql/min_mysql.h"

extern DB db;

// seconds
int getWaitingTime(const RentRequest& request) {
	QString skel = R"(
select *
from rentedCarView
where carTypeId = %1
  and startLocationId = %2
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
