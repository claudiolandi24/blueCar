#ifndef CREDITCARD_H
#define CREDITCARD_H

#include "rbk/minMysql/sqlRow.h"
#include <QList>
#include <QString>

class CreditCard {
      public:
	long long id = 0;
	QString   hash;

	CreditCard() = default;
	static CreditCard        getNewCreditCardFromTerminal();
	static CreditCard        getCreditCardFromSqlRow(const sqlRow& row);
	static QList<CreditCard> getCreditCardsFromDb(const QString& whereCondition = QString());

	void setHashFromTerminal();
	
    void saveToDb();
    void updateInDb();
};

#endif // CREDITCARD_H
