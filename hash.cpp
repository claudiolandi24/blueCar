#include "hash.h"
#include <QCryptographicHash>

//TODO
QString getHash(const QString& string) {
    //TODO remove
    return "HASH_OF_"+string;
    
	QByteArray qbaString = string.toUtf8();
	QByteArray hash      = QCryptographicHash::hash(qbaString, QCryptographicHash::RealSha3_512);
	QString    strHash   = QString(hash.toHex());
	return strHash;
}
