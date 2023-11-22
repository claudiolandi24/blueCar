#include "try.h"
#include "rbk/minMysql/min_mysql.h"
#include <QTextStream>

extern DB db;
//using namespace Qt;

void tryQPrint() {
	QTextStream(stdout) << "Hello World" << Qt::endl;
	QTextStream(stdout) << "Hello World2" << Qt::endl;
}

#include "car.h"
void try0() {
//	QTextStream(stdout) << "type\n";
//	QString s = QTextStream(stdin).readLine();
//	QTextStream(stdout) << "value is '" << s << "'\n";
    
    
    
//    auto res = db.query("select * from db1.persons");
//    int b = 0;
//    Q_UNUSED(b);
    
    auto car = Car::getNewCarFromUser();
    car.saveToDb();
    
    
}
