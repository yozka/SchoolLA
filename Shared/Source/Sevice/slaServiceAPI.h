#pragma once
#include <QtQml>


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
		qmlRegisterType<AServiceAPI>("com.sla.api", 1, 0, "AServiceAPI");
	}

	//������
	QNetworkReply *handleRequest(QString path, QStringList sort,
		QVariantMap filters = QVariantMap(),
		QStringList fields = QStringList(), QStringList expand = QStringList(),
		QString id = 0) override;


	//�������� ������ �������
	QNetworkReply *getGrade(const int schoolID);
	

};