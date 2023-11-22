#include "try.h"
#include <QTextStream>

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
    
    Car::getNewCarFromUser();
    
}
