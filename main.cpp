#include "database.h"
#include "menulogin.h"
#include "try.h"
#include <QCoreApplication>
#include <iostream>

using namespace std;

//TODO
// more simple now
void myMessageOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
	QByteArray  localMsg = msg.toLocal8Bit();
	QDateTime   qdtNow   = QDateTime::currentDateTimeUtc();
	QByteArray  qbaNow   = qdtNow.toString("yyyy-MM-dd hh:mm:ss UTC").toLocal8Bit();
	const char* now      = qbaNow.constData();

	switch (type) {
	case QtDebugMsg:
		fprintf(stderr, "%s\nDebug: %s (%s:%u, %s)\n", now, localMsg.constData(), context.file, context.line, context.function);
        fprintf(stderr, "------------------------------------------------------------------------------------------------------\n\n\n\n");
		break;
	case QtInfoMsg:
		fprintf(stderr, "%s\nInfo: %s (%s:%u, %s)\n", now, localMsg.constData(), context.file, context.line, context.function);
        fprintf(stderr, "------------------------------------------------------------------------------------------------------\n\n\n\n");
		break;
	case QtWarningMsg:
		fprintf(stderr, "%s\nWarning: %s (%s:%u, %s)\n", now, localMsg.constData(), context.file, context.line, context.function);
        fprintf(stderr, "------------------------------------------------------------------------------------------------------\n\n\n\n");
		break;
	case QtCriticalMsg:
		fprintf(stderr, "%s\nCritical: %s (%s:%u, %s)\n", now, localMsg.constData(), context.file, context.line, context.function);
        fprintf(stderr, "------------------------------------------------------------------------------------------------------\n\n\n\n");
		break;
	case QtFatalMsg:
		fprintf(stderr, "%s\nFatal: %s (%s:%u, %s)\n", now, localMsg.constData(), context.file, context.line, context.function);
        fprintf(stderr, "------------------------------------------------------------------------------------------------------\n\n\n\n");
		abort();
	}
}

// ./blueCar 2>> error.log
int main() {
	qInstallMessageHandler(myMessageOutput);

	initDb();

	//runApplication();
	try0();

	return 0;
}

//TODO IMP
/*
when insert pwd or credit card do not show typed
----------

config file



*/
