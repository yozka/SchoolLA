#pragma once
#include <QtQml>
#include <QObject>

#include "..\API\ssApibase.h"
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// ��������� API ��� ������� � �������
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

	//������
	QNetworkReply *handleRequest(const QString &path,
		const QVariantMap		&parameters = QVariantMap(),
		const QStringList		&sort = QStringList(),
		const API::APagination	*pagination = nullptr,
		const QVariantMap		&filters = QVariantMap(),
		const QStringList		&fields = QStringList(),
		const QStringList		&expand = QStringList(),
		const QString			&id = QString()) override;


	//�������� ������ �������
	QNetworkReply *getGrade(const int schoolID);
	

};