#include "ssAbstractJsonListModel.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkReply>
#include <QJsonDocument>
///----------------------------------------------------------------------------



///----------------------------------------------------------------------------
using namespace API;
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// constructor
/// 
///
///----------------------------------------------------------------------------
AAbstractJsonListModel :: AAbstractJsonListModel(QObject *parent) 
	: 
		ABaseListModel(parent)
{
    //setAccept("application/json");
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
QVariantList AAbstractJsonListModel::getVariantList(const QByteArray &bytes)
{
    const QString str = QString::fromUtf8(bytes.constData(), bytes.size());

    QJsonParseError parseError;
    const QJsonDocument document = QJsonDocument::fromJson(bytes, &parseError);
    const QJsonArray jsonArray = document.array();

    if (parseError.error != QJsonParseError::NoError) 
	{
        qDebug() << parseError.errorString();
    }

    return jsonArray.toVariantList();
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
QVariantMap AAbstractJsonListModel :: getVariantMap(const QByteArray &bytes)
{
    const QString str = QString::fromUtf8(bytes.constData(), bytes.size());

    QJsonParseError parseError;
    const QJsonDocument document = QJsonDocument::fromJson(bytes, &parseError);
    const QJsonObject obj = document.object();

    if (parseError.error != QJsonParseError::NoError) 
	{
        qDebug() << parseError.errorString();
    }

    return obj.toVariantMap();
}
