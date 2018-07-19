#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "..\..\..\Shared\Source\Sevice\slaServiceAPI.h"
#include "..\..\..\Shared\Source\API\Models\ssJsonListModel.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);



    QGuiApplication app(argc, argv);

    AServiceAPI::declareQML();
    API::AJsonListModel::declareQML();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main/Main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
