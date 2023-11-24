#include "creditcard.h"
#include "hash.h"
#include "rbk/minMysql/min_mysql.h"
#include "validate.h"

extern DB db;

void CreditCard::setHashFromTerminal() {
	QString number     = getValidatedString("Insert the credit card number", make_unique<ValidateCreditCardNumber>());
	QString date       = getValidatedString("Insert the credit card expiration date", make_unique<ValidateCreditCardDate>());
	QString secureCode = getValidatedString("Insert the credit card secure code", make_unique<ValidateCreditCardSecureCode>());
	hash               = getHash(number + date + secureCode);
}

CreditCard CreditCard::getNewCreditCardFromTerminal() {
	CreditCard card;
	card.setHashFromTerminal();
	return card;
}

CreditCard CreditCard::getCreditCardFromSqlRow(const sqlRow& row) {
	CreditCard card;
	row.get2("id", card.id);
	row.get2("hash", card.hash);
	return card;
}

QList<CreditCard> CreditCard::getCreditCardsFromDb(const QString& whereCondition) {
	auto skel = QSL("select * from creditCard %1;");
	auto sql  = skel.arg(whereCondition);
	auto res  = db.query(sql);

	QList<CreditCard> cards;
	for (const auto& row : res) {
		cards.push_back(CreditCard::getCreditCardFromSqlRow(row));
	}
	return cards;
}

void CreditCard::saveToDb() {
	QString skel = R"(
INSERT INTO creditCard
set hash = '%1';
)";
	auto    sql  = skel.arg(hash);
	db.query(sql);
	id = (long long)(db.lastId());
}
