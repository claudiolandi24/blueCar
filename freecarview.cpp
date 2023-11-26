#include "freecarview.h"

Car FreeCarView::getCarFromSqlRow(const sqlRow& row) {
    //qDebug().noquote() << "sqlRow row =\n"<<row.serialize()<<"\n"<<QStacker16Light();
	Car car;
	row.get2("carId", car.id);
	car.active=1;
	row.get2("carTypeId", car.typeId);
	row.get2("licensePlate", car.licensePlate);
	row.get2("brand", car.brand);
	row.get2("name", car.name);
	row.get2("locationId", car.locationId);
	row.get2("totalDistanceTraveled", car.totalDistanceTraveled);
	return car;
}

