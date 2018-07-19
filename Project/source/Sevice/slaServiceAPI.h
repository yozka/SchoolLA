#pragma once
#include <QtQml>
#include <QObject>

#include "..\API\ssApibase.h"
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// Основоное API для доступа к сервису
/// 
///
///----------------------------------------------------------------------------
class AServiceAPI 
	: 
		public API::APIBase
{
	Q_OBJECT
public:
	Q_INVOKABLE explicit AServiceAPI();

	static void declareQML() 
	{
		qmlRegisterType<AServiceAPI>("com.sla.serviceapi", 1, 0, "AServiceAPI");
	}

	//запрос
	QNetworkReply *handleRequest(const QString &path,
		const QVariantMap		&parameters = QVariantMap(),
		const QStringList		&sort = QStringList(),
		const API::APagination	*pagination = nullptr,
		const QVariantMap		&filters = QVariantMap(),
		const QStringList		&fields = QStringList(),
		const QStringList		&expand = QStringList(),
		const QString			&id = QString()) override;


	//получить список занятий
	QNetworkReply *getGrade(const int schoolID);
	


private:

	//формирование запроса по умолчанию
	QNetworkReply *defaultRequest(const QString &path,
		const QVariantMap		&parameters = QVariantMap(),
		const QStringList		&sort = QStringList(),
		const API::APagination	*pagination = nullptr,
		const QVariantMap		&filters = QVariantMap(),
		const QStringList		&fields = QStringList(),
		const QStringList		&expand = QStringList(),
		const QString			&id = QString());
};