#ifndef CREDITCARD_H
#define CREDITCARD_H

#include <QString>

class CreditCard {
      public:
	long long id = 0;
	QString   hash;

	CreditCard() = default;
    static CreditCard getNewCreditCardFromTerminal();
    
    void setHashFromTerminal();
    void saveToDb();
};

#endif // CREDITCARD_H
