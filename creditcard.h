#ifndef CREDITCARD_H
#define CREDITCARD_H

#include <QString>

class CreditCard {
      public:
	long long id = 0;
	QString   number;
	// MM/AAAA
	QString expirationDate;
	QString secureCode;

	CreditCard() = default;
};

#endif // CREDITCARD_H
