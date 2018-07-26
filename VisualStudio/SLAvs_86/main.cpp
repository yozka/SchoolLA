#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>

#include "..\..\Project\source\Sevice\slaServiceAPI.h"
#include "..\..\Project\source\API\Models\ssJsonListModel.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

	QGuiApplication app(argc, argv);

	//QQuickStyle::setStyle("Material");
	QTranslator translator;
	translator.load("sla_ru", ":/translations");
	app.installTranslator(&translator);

	AServiceAPI::declareQML();
	API::AJsonListModel::declareQML();

	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/main/Main.qml")));
	if (engine.rootObjects().isEmpty())
	{
		return -1;
	}
	return app.exec();
}
