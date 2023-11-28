#include "database.h"
#include "menulogin.h"
#include "rbk/QStacker/qstacker.h"
#include "rbk/caching/apcu2.h"
#include "try.h"
#include <QCoreApplication>
#include <iostream>
#include <stdexcept>

using namespace std;

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

void startupfun(void) __attribute__((constructor));

void startupfun(void) {
	APCU::disableAPCU = true;
}

// ./blueCar 2>> error.log
int main() {
	try {
		qInstallMessageHandler(myMessageOutput);
		initDb();

		runApplication();
		//try0();

	} catch (const std::exception& ex) {
		qCritical().noquote() << ex.what() << "\n"
		                      << QStacker16Light();
		cout << "An error has occurred. The Program will now be terminated\n";
	}

	return 0;
}
