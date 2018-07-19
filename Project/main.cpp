#include <QGuiApplication>
#include <QQmlApplicationEngine>


#include "source/Sevice/slaServiceAPI.h"
#include "source/API/Models/ssJsonListModel.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    //QQuickStyle::setStyle("Material");

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
