#include "try.h"
#include "car.h"
#include "hash.h"
#include "menulogin.h"
#include "rbk/QStacker/qstacker.h"
#include "rbk/minMysql/min_mysql.h"
#include "user.h"
#include "validate.h"
#include "variadictable.h"
#include <QTextStream>
#include <iostream>

using namespace std;

void try0() {
	cout << getHash("admin").toStdString();
}
