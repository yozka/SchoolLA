#include <QApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>


#include "Source\Sevice\slaServiceAPI.h"

/*
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>



QNetworkReply *reply = NULL;

void someFunction()
{
	QString st;
	if (reply->error() == QNetworkReply::NoError)
	{
		QByteArray content = reply->readAll();
		QJsonDocument d = QJsonDocument::fromJson(content);
		auto v = d.toVariant().toList();
		for (const auto &item : v)
		{
			const auto mp = item.toMap();
			int gradeID = mp["gradeID"].toInt();
			int schoolID = mp["schoolID"].toInt();
			QDateTime beginDate = mp["beginDate"].toDateTime();
			QDateTime endDate = mp["endDate"].toDateTime();
			QString name = mp["name"].toString();


			int dii = 0;
		}

		int i = 0;
	}
	else
	{
		st = reply->errorString();
	}
	reply->deleteLater();
}
*/



int main(int argc, char *argv[])
{
	QGuiApplication::setApplicationName("SLA");
	QGuiApplication::setApplicationVersion("1.0");
	QGuiApplication::setOrganizationName("Seragam");
	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);


	QGuiApplication app(argc, argv);

	
	AServiceAPI::declareQML();

	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/main/main.qml")));




	/*

	QUrl url = QString("https://sla.tigraha.com/api/1.0/grade/?schoolID=1");
	QNetworkRequest req(url);
	req.setSslConfiguration(QSslConfiguration::defaultConfiguration());

	
	

	req.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json; charset=utf-8"));
	//req.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(jsonPost.size()));

	auto manager = new QNetworkAccessManager();


	//Sending the Request
	reply = manager->get(req);
	bool ok = QObject::connect(reply, &QNetworkReply::finished, someFunction);
		

	*/




/*
	HandlerSignals *handlerSignals = new HandlerSignals(root);
	QObject::connect(root, SIGNAL(qmlSignal(QString)),
		handlerSignals, SLOT(cppSlot(QString)));


		1
		signal qmlSignal(string msg)
		onClicked: {qmlSignal("€блок")}

		*/
	return app.exec();
}








/*
class Animal
{
public:
Animal(const QString &type, const QString &size);
...
};

class AnimalModel : public QAbstractListModel
{
Q_OBJECT
public:
enum AnimalRoles {
TypeRole = Qt::UserRole + 1,
SizeRole
};

AnimalModel(QObject *parent = 0);
...
};

QHash<int, QByteArray> AnimalModel::roleNames() const {
QHash<int, QByteArray> roles;
roles[TypeRole] = "type";
roles[SizeRole] = "size";
return roles;
}

int main(int argc, char ** argv)
{
QGuiApplication app(argc, argv);

AnimalModel model;
model.addAnimal(Animal("Wolf", "Medium"));
model.addAnimal(Animal("Polar bear", "Large"));
model.addAnimal(Animal("Quoll", "Small"));

QQuickView view;
view.setResizeMode(QQuickView::SizeRootObjectToView);
QQmlContext *ctxt = view.rootContext();
ctxt->setContextProperty("myModel", &model);
...
This model is displayed by a ListView delegate that accesses the type and size roles:

ListView {
width: 200; height: 250

model: myModel
delegate: Text { text: "Animal: " + type + ", " + size }
}

*/