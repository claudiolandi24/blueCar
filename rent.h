#ifndef RENT_H
#define RENT_H

#include <QDateTime>

class Rent {
      public:
	long long id              = 0;
	long long userId          = 0;
	int       carId           = 0;
	int       startLocationId = 0;
	// UTC
	QDateTime startDateTime;
	int       endLocationId = 0;
	// UTC
	QDateTime endDateTime;
	// UTC
	QDateTime estimatedEndDateTime;
	// km
	int distance;
	// $ cent
	int cost;

	Rent() = default;
	void saveInDb();
};

#endif // RENT_H
