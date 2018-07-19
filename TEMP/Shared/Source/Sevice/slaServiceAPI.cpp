#include "slaServiceAPI.h"


#include <QFile>
#include <QTextStream>
#include <QUrlQuery>
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// Constructor
/// 
///
///----------------------------------------------------------------------------
AServiceAPI :: AServiceAPI() 
	: 
		API::APIBase(0)
{
	//setAccept("application/json; charset=utf-8");
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// ��������� ��������
/// 
///
///----------------------------------------------------------------------------
QNetworkReply *AServiceAPI :: handleRequest(
		const QString			&path,
		const QVariantMap		&parameters,
		const QStringList		&sort,
		const API::APagination	*pagination,
		const QVariantMap		&filters,
		const QStringList		&fields,
		const QStringList		&expand,
		const QString			&id)
{
	/*
	if (path == "grade")
	{
		return getGrade(1);
	}*/


	return defaultRequest(path, parameters, sort, pagination, filters, fields, expand, id);
}
///----------------------------------------------------------------------------





 ///---------------------------------------------------------------------------
///
/// ������������ ������� �� ���������
/// 
///
///----------------------------------------------------------------------------
QNetworkReply *AServiceAPI::defaultRequest(
				const QString			&path,
				const QVariantMap		&parameters,
				const QStringList		&sort,
				const API::APagination	*pagination,
				const QVariantMap		&filters,
				const QStringList		&fields,
				const QStringList		&expand,
				const QString			&id)
{
	QString adr = API::utils::makeSeparator(baseUrl()) + API::utils::makeSeparator(path);
	QUrl url = QUrl(adr);
	QUrlQuery query;

	for (const auto &key : parameters.keys())
	{
		query.addQueryItem(key, parameters.value(key).toString());
	}
	url.setQuery(query.query());


	QNetworkReply *reply = get(url);
	return reply;
}
///----------------------------------------------------------------------------





 ///---------------------------------------------------------------------------
///
/// �������� ������ �������
/// 
///
///----------------------------------------------------------------------------
QNetworkReply *AServiceAPI :: getGrade(const int schoolID)
{
	QUrl url = QUrl(baseUrl() + "/1.0/grade/");
	QUrlQuery query;
	query.addQueryItem("schoolID", QString::number(schoolID));



	url.setQuery(query.query());


	QNetworkReply *reply = get(url);

	return reply;
}


/*
//In this methods we get list of objects, based on specified page number, filters, sort and fileds list.
//We can fetch all fields or only needed in our list.
QNetworkReply *AServiceAPI::getCoupons(QStringList sort, Pagination *pagination, QVariantMap filters, QStringList fields)
{
	//URL and GET parameters
	QUrl url = QUrl(baseUrl() + "/v1/coupon");
	QUrlQuery query;

	//Specify sort GET param
	if (!sort.isEmpty()) {
		query.addQueryItem("sort", sort.join(","));
	}

	//Specify pagination. We use pagination type from model.
	switch (pagination->policy()) {
	case Pagination::PageNumber:
		query.addQueryItem("per-page", QString::number(pagination->perPage()));
		query.addQueryItem("page", QString::number(pagination->currentPage()));
		break;
	case Pagination::None:
	case Pagination::Infinity:
	case Pagination::LimitOffset:
	case Pagination::Cursor:
	default:
		break;
	}

	//if we need to filter our model, we use filters.
	//Be careful, if you use this methods, your curent pagintaion wil be broken
	//and you must full reaload your model data when you specify new filters

	if (!filters.isEmpty()) {
		QMapIterator<QString, QVariant> i(filters);
		while (i.hasNext()) {
			i.next();
			query.addQueryItem(i.key(), i.value().toString());
		}
	}

	//We may to get all or spicified fields in this method.
	if (!fields.isEmpty()) {
		query.addQueryItem("fields", fields.join(","));
	}

	url.setQuery(query.query());

	QNetworkReply *reply = get(url);

	return reply;
}
*/


/*
//If we fetch e.g. 3 of 10 fields in our 'getCoupons' methods,
//we may to get full information from needed item by it ID
QNetworkReply *AServiceAPI::getCouponDetail(QString id)
{
	if (id.isEmpty()) {
		qDebug() << "ID is empty!";
		return 0;
	}

	QUrl url = QUrl(baseUrl() + "/v1/coupon/" + id);

	QNetworkReply *reply = get(url);

	return reply;
}

QNetworkReply *AServiceAPI::getCategories(QStringList sort, Pagination *pagination)
{
	//URL and GET parameters
	QUrl url = QUrl(baseUrl() + "/v1/categories");
	QUrlQuery query;

	//Specify sort GET param
	if (!sort.isEmpty()) {
		query.addQueryItem("sort", sort.join(","));
	}

	//Specify pagination. We use pagination type from model.
	switch (pagination->policy()) {
	case Pagination::PageNumber:
		query.addQueryItem("per-page", QString::number(pagination->perPage()));
		query.addQueryItem("page", QString::number(pagination->currentPage()));
		break;
	case Pagination::None:
	case Pagination::Infinity:
	case Pagination::LimitOffset:
	case Pagination::Cursor:
	default:
		break;
	}

	url.setQuery(query.query());

	QNetworkReply *reply = get(url);

	return reply;
}*/