#pragma once

#include <QObject>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QHttpMultiPart>

#include "Models\ssPagination.h"
///----------------------------------------------------------------------------


namespace API
{
	///----------------------------------------------------------------------------






	///---------------------------------------------------------------------------
   ///
   /// ��������� API ��� ������� � �������
   /// 
   ///
   ///----------------------------------------------------------------------------
	class APIBase
		:
		public QObject
	{
		Q_OBJECT
	public:
		explicit APIBase(QObject *parent = nullptr);
		bool checkReplyIsError(QNetworkReply *reply);

			//Accept header for JSON data
			Q_PROPERTY(QByteArray accept READ accept WRITE setAccept NOTIFY acceptChanged)
			Q_PROPERTY(QByteArray acceptHeader READ acceptHeader WRITE setAcceptHeader NOTIFY acceptHeaderChanged)
			Q_PROPERTY(QByteArray contentType READ contentType WRITE setContentType NOTIFY contentTypeChanged)
			Q_PROPERTY(QByteArray contentTypeHeader READ contentTypeHeader WRITE setContentTypeHeader NOTIFY contentTypeHeaderChanged)
			
			//Specify Auth token for each request. Set this before run your requests (You may use Basic auth and Bearer token auth)
			Q_PROPERTY(QByteArray baseUrl READ baseUrl WRITE setBaseUrl NOTIFY baseUrlChanged)

			//Specify Auth token for each request. Set this before run your requests (You may use Basic auth and Bearer token auth)
			Q_PROPERTY(QByteArray authToken READ authToken WRITE setAuthToken NOTIFY authTokenChanged)
			
			//Specify Auth token header name. Default is 'Authorization' (You may use Basic auth and Bearer token auth)
			Q_PROPERTY(QByteArray authTokenHeader READ authTokenHeader WRITE setAuthTokenHeader NOTIFY authTokenHeaderChanged)
			//--------------------

		QByteArray baseUrl() const;
		QByteArray accept() const;
		QByteArray acceptHeader() const;
		QByteArray contentType() const;
		QByteArray contentTypeHeader() const;
		QByteArray authToken() const;
		QByteArray authTokenHeader() const;

		virtual QNetworkReply *handleRequest(const QString &path, 
			const QVariantMap	&parameters = QVariantMap(),
			const QStringList	&sort		= QStringList(),
			const APagination	*pagination = nullptr,
			const QVariantMap	&filters	= QVariantMap(),
			const QStringList	&fields		= QStringList(), 
			const QStringList	&expand		= QStringList(),
			const QString		&id			= QString())
		{
				Q_UNUSED(path)
				Q_UNUSED(parameters)
				Q_UNUSED(sort)
				Q_UNUSED(filters)
				Q_UNUSED(fields)
				Q_UNUSED(expand)
				Q_UNUSED(id)
				return 0;
		};

	public slots:
		void setBaseUrl(QByteArray baseUrl);
		void setAccept(QString accept);
		void setAcceptHeader(QByteArray acceptHeader);
		void setContentType(QString contentType);
		void setContentTypeHeader(QByteArray contentTypeHeader);
		void setAuthToken(QByteArray authToken);
		void setAuthTokenHeader(QByteArray authTokenHeader);

	signals:
		void replyError(QNetworkReply *reply, QNetworkReply::NetworkError error, QString errorString);
		void acceptChanged(QByteArray accept);
		void baseUrlChanged(QByteArray baseUrl);
		void acceptHeaderChanged(QByteArray acceptHeader);
		void contentTypeChanged(QByteArray contentType);
		void contentTypeHeaderChanged(QByteArray contentTypeHeader);
		void authTokenChanged(QByteArray authToken);
		void authTokenHeaderChanged(QByteArray authTokenHeader);

	protected:
		QNetworkReply *get(QUrl url);
		QNetworkReply *post(QUrl url);
		QNetworkReply *post(QUrl url, QIODevice *data);
		QNetworkReply *post(QUrl url, const QByteArray &data);
		QNetworkReply *post(QUrl url, QHttpMultiPart *multiPart);
		QNetworkReply *put(QUrl url);
		QNetworkReply *put(QUrl url, QIODevice *data);
		QNetworkReply *put(QUrl url, const QByteArray &data);
		QNetworkReply *put(QUrl url, QHttpMultiPart *multiPart);
		QNetworkReply *patch(QUrl url);
		QNetworkReply *patch(QUrl url, QIODevice *data);
		QNetworkReply *patch(QUrl url, const QByteArray &data);
		QNetworkReply *patch(QUrl url, QHttpMultiPart *multiPart);
		QNetworkReply *deleteResource(QUrl url);
		QNetworkReply *head(QUrl url);
		QNetworkReply *options(QUrl url);

		QNetworkAccessManager *manager;

		virtual QNetworkRequest createRequest(const QUrl &url) const;

		void setRawHeaders(QNetworkRequest *request);
		void connectReplyToErrors(QNetworkReply *reply);

		protected slots:
		void replyFinished(QNetworkReply *reply);
		void handleReplyError(QNetworkReply::NetworkError error);
		void handleSslErrors(QList<QSslError> errors);

	private:
		QByteArray mAccept;
		QByteArray mBaseUrl;
		QByteArray mAcceptHeader;
		QByteArray mContentType;
		QByteArray mContentTypeHeader;
		QByteArray mAuthToken;
		QByteArray mAuthTokenHeader;
	};


}