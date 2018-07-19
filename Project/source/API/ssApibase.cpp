#include "ssApibase.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
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
APIBase :: APIBase(QObject *parent) 
	: 
		QObject(parent), 
        mAcceptHeader("Accept"),
		mContentTypeHeader("Content-Type"), 
		mAuthTokenHeader("Authorization")
{
    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(replyFinished(QNetworkReply *)));
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
void APIBase::replyFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) 
	{
        qDebug() << reply->error() << reply->errorString();
        emit replyError(reply, reply->error(), reply->errorString());
    }
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
void APIBase :: handleReplyError(QNetworkReply::NetworkError error)
{
    qDebug() << "Error" << error;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
void APIBase::handleSslErrors(QList<QSslError> errors)
{
    qDebug() << errors;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
void APIBase::setRawHeaders(QNetworkRequest *request)
{
    request->setRawHeader(acceptHeader(), accept());
    request->setRawHeader(authTokenHeader(), authToken());
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
void APIBase::connectReplyToErrors(QNetworkReply *reply)
{
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(handleReplyError(QNetworkReply::NetworkError)));

    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
            this, SLOT(handleSslErrors(QList<QSslError>)));
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
bool APIBase::checkReplyIsError(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) 
	{
        qDebug() << reply->rawHeaderList();
        qDebug() << reply->bytesAvailable() << reply->errorString();
        return true;
    } 
	else 
	{
        return false;
    }
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
QByteArray APIBase :: accept() const
{
    return mAccept;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
QByteArray APIBase :: baseUrl() const
{
    return mBaseUrl;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
QByteArray APIBase :: acceptHeader() const
{
    return mAcceptHeader;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
QByteArray APIBase :: contentType() const
{
    return mContentType;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
QByteArray APIBase :: contentTypeHeader() const
{
    return mContentTypeHeader;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
QByteArray APIBase :: authToken() const
{
    return mAuthToken;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
QByteArray APIBase :: authTokenHeader() const
{
    return mAuthTokenHeader;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
void APIBase :: setAccept(QString accept)
{
    QByteArray newData;
    newData.append(accept);

    if (mAccept == newData)
        return;

    mAccept = newData;
    emit acceptChanged(newData);
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
void APIBase :: setBaseUrl(QByteArray baseUrl)
{
    if (mBaseUrl == baseUrl)
        return;

    mBaseUrl = baseUrl;
    emit baseUrlChanged(baseUrl);
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
void APIBase :: setAcceptHeader(QByteArray acceptHeader)
{
    if (mAcceptHeader == acceptHeader)
        return;

    mAcceptHeader = acceptHeader;
    emit acceptHeaderChanged(acceptHeader);
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
void APIBase :: setContentType(QString contentType)
{
    QByteArray newData;
    newData.append(contentType);

    if (mContentType == newData)
        return;

    mContentType = newData;
    emit contentTypeChanged(newData);
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
void APIBase :: setContentTypeHeader(QByteArray contentTypeHeader)
{
    if (mContentTypeHeader == contentTypeHeader)
        return;

    mContentTypeHeader = contentTypeHeader;
    emit contentTypeHeaderChanged(contentTypeHeader);
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
void APIBase :: setAuthToken(QByteArray authToken)
{
    if (mAuthToken == authToken)
        return;

    mAuthToken = authToken;
    emit authTokenChanged(authToken);
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
void APIBase::setAuthTokenHeader(QByteArray authTokenHeader)
{
    if (mAuthTokenHeader == authTokenHeader)
        return;

    mAuthTokenHeader = authTokenHeader;
    emit authTokenHeaderChanged(authTokenHeader);
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
QNetworkReply *APIBase :: get(QUrl url)
{
    QNetworkRequest request = createRequest(url);
	setRawHeaders(&request);
    QNetworkReply *reply = manager->get(request);
    connectReplyToErrors(reply);
    return reply;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
QNetworkReply *APIBase :: post(QUrl url)
{
    QNetworkRequest request = createRequest(url);
    setRawHeaders(&request);

    QNetworkReply *reply = manager->sendCustomRequest(request, "POST");
    connectReplyToErrors(reply);
    return reply;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
QNetworkReply *APIBase::post(QUrl url, QIODevice *data)
{
    QNetworkRequest request = createRequest(url);
    setRawHeaders(&request);
    if (!contentType().isEmpty()) 
	{
        request.setRawHeader(contentTypeHeader(), contentType());
    }

    QNetworkReply *reply = manager->post(request, data);
    connectReplyToErrors(reply);
    return reply;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
QNetworkReply *APIBase :: post(QUrl url,const QByteArray &data)
{
    QNetworkRequest request = createRequest(url);
    setRawHeaders(&request);
    if (!contentType().isEmpty()) 
	{
        request.setRawHeader(contentTypeHeader(), contentType());
    }

    QNetworkReply *reply = manager->post(request, data);
    connectReplyToErrors(reply);
    return reply;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
QNetworkReply *APIBase :: post(QUrl url, QHttpMultiPart *multiPart)
{
    QNetworkRequest request = createRequest(url);
    setRawHeaders(&request);

    QNetworkReply *reply = manager->post(request, multiPart);
    connectReplyToErrors(reply);
    return reply;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
QNetworkReply *APIBase :: put(QUrl url)
{
    QNetworkRequest request = createRequest(url);
    setRawHeaders(&request);

    QNetworkReply *reply = manager->sendCustomRequest(request, "PUT");
    connectReplyToErrors(reply);
    return reply;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
QNetworkReply *APIBase :: put(QUrl url, QIODevice *data)
{
    QNetworkRequest request = createRequest(url);
    setRawHeaders(&request);
    if (!contentType().isEmpty()) 
	{
        request.setRawHeader(contentTypeHeader(), contentType());
    }

    QNetworkReply *reply = manager->put(request, data);
    connectReplyToErrors(reply);
    return reply;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
QNetworkReply *APIBase :: put(QUrl url, const QByteArray &data)
{
    QNetworkRequest request = createRequest(url);
    setRawHeaders(&request);
    if (!contentType().isEmpty()) 
	{
        request.setRawHeader(contentTypeHeader(), contentType());
    }

    QNetworkReply *reply = manager->put(request, data);
    connectReplyToErrors(reply);
    return reply;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
QNetworkReply *APIBase :: put(QUrl url, QHttpMultiPart *multiPart)
{
    QNetworkRequest request = createRequest(url);
    setRawHeaders(&request);

    QNetworkReply *reply = manager->put(request, multiPart);
    connectReplyToErrors(reply);
    return reply;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
QNetworkReply *APIBase::patch(QUrl url)
{
    QNetworkRequest request = createRequest(url);
    setRawHeaders(&request);

    QNetworkReply *reply = manager->sendCustomRequest(request, "PATCH");
    connectReplyToErrors(reply);
    return reply;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
QNetworkReply *APIBase::patch(QUrl url, QIODevice *data)
{
    QNetworkRequest request = createRequest(url);
    setRawHeaders(&request);
    if (!contentType().isEmpty()) 
	{
        request.setRawHeader(contentTypeHeader(), contentType());
    }

    QNetworkReply *reply = manager->sendCustomRequest(request, "PATCH", data);
    connectReplyToErrors(reply);
    return reply;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
QNetworkReply *APIBase::patch(QUrl url, const QByteArray &data)
{
    QNetworkRequest request = createRequest(url);
    setRawHeaders(&request);
    if (!contentType().isEmpty())
	{
        request.setRawHeader(contentTypeHeader(), contentType());
    }

    QNetworkReply *reply = manager->sendCustomRequest(request, "PATCH", data);
    connectReplyToErrors(reply);
    return reply;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
QNetworkReply *APIBase :: patch(QUrl url, QHttpMultiPart *multiPart)
{
    QNetworkRequest request = createRequest(url);
    setRawHeaders(&request);

    QNetworkReply *reply = manager->sendCustomRequest(request, "PATCH", multiPart);
    connectReplyToErrors(reply);
    return reply;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
QNetworkReply *APIBase::deleteResource(QUrl url)
{
    QNetworkRequest request = createRequest(url);
    setRawHeaders(&request);

    QNetworkReply *reply = manager->deleteResource(request);
    connectReplyToErrors(reply);
    return reply;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
QNetworkReply *APIBase :: head(QUrl url)
{
    QNetworkRequest request = createRequest(url);
    setRawHeaders(&request);

    QNetworkReply *reply = manager->head(request);
    connectReplyToErrors(reply);
    return reply;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
QNetworkReply *APIBase::options(QUrl url)
{
    QNetworkRequest request = createRequest(url);
    setRawHeaders(&request);

    QNetworkReply *reply = manager->sendCustomRequest(request, "OPTIONS");
    connectReplyToErrors(reply);
    return reply;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
QNetworkRequest APIBase :: createRequest(const QUrl &url) const
{
    QNetworkRequest req(url);
	req.setSslConfiguration(QSslConfiguration::defaultConfiguration());
	return req;
}
