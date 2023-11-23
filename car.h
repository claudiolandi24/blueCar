#ifndef CAR_H
#define CAR_H

#include "rbk/minMysql/sqlRow.h"
#include <QList>
#include <QPair>

class Car {
      private:
	static QPair<bool, int> getCarIdFromUser(const QString& operation);
	static bool             carIdExists(int carId);

      public:
	// db id
	int     id     = 0;
	int     typeId = 0;
	QString licensePlate;
	QString brand;
	QString name;
	bool    isFree                = true;
	int     locationId            = 0;
	int     totalDistanceTraveled = 0;

	Car() = default;
	static Car        getCarFromSqlRow(sqlRow row);
	static Car        getNewCarFromUser();
	static Car        getCarFromDb(int id);
	static QList<Car> getCarsFromDb(const QString& whereCondition = QString());
	static void       printAllCarsAsTable();
	static void       printCarsAsTable(const QList<Car>& cars);
	void              printAsTable();
	static void       deleteCarAfterUserRequest();
	static void       updateCarAfterUserRequest();
	static void       deleteCarFromDb(int id);

	void saveToDb();
	void updateInDb();

	void setTypeFromUser();
	void setLicensePlateFromUser();
	void setBrandFromUser();
	void setNameFromUser();
	void setLocationFromUser();
	void setDistanceTraveledFromUser();
};

#endif // CAR_H
