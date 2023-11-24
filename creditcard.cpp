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

void CreditCard::saveToDb() {
	QString skel = R"(
INSERT INTO creditCard
set hash = %1;
)";
	auto    sql  = skel.arg(hash);
	try {
		db.query(sql);
		id = (long long)(db.lastId());
	} catch (const ExceptionV2& e) {
        
	}
}
