#ifndef CAR_H
#define CAR_H

#include <QString>
#include <QVector>

class Car {
      private:
	// db id
	int     id     = 0;
	int     typeId = 0;
	QString licensePlate;
	QString brand;
	QString name;
	bool    isFree                = true;
	int     locationId            = 0;
	int     totalDistanceTraveled = 0;

      public:
	Car();
	static Car          getNewCarFromUser();
	static Car          getCarFromDb(int id);
	static QVector<Car> getAllCarsFromDb();
	static void         deleteCarFromDb(int id);

	void saveToDb();
	void updateInDb();
};

#endif // CAR_H
