#ifndef CAR_H
#define CAR_H

#include <QPair>
#include <QString>
#include <QVector>

class Car {
      private:
	static QPair<bool, int> getCarIdFromUser();
    static bool carIdExists(int carId);

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
	static Car          getNewCarFromUser();
	static Car          getCarFromDb(int id);
	static QVector<Car> getAllCarsFromDb();
	static void         deleteCarAfterUserRequest();
	static void         deleteCarFromDb(int id);

	void saveToDb();
	void updateInDb();
};

#endif // CAR_H
