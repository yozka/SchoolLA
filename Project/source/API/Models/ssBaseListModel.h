#pragma once

#include <QAbstractListModel>
#include <QQmlPropertyMap>
#include <QNetworkReply>

#include "ssItem.h"
#include "ssPagination.h"
#include "ssDetailsModel.h"
#include "..\ssApibase.h"
///----------------------------------------------------------------------------


namespace API
{
	///----------------------------------------------------------------------------






	 ///---------------------------------------------------------------------------
	///
	/// ќсновна¤ модель списка данных
	/// 
	///
	///----------------------------------------------------------------------------
	class ABaseListModel 
		: 
			public QAbstractListModel
	{
		Q_OBJECT
		
	friend ADetailsModel;
	public:
		ABaseListModel(QObject *parent = 0);

			Q_PROPERTY(APIBase *api READ apiInstance WRITE setApiInstance NOTIFY apiInstanceChanged)

			//--------------------
			//Standard HATEOAS REST API params (https://en.wikipedia.org/wiki/HATEOAS, for example: https://github.com/yiisoft/yii2/blob/master/docs/guide-ru/rest-quick-start.md)
			//Specify sorting fields
			Q_PROPERTY(QStringList sort READ sort WRITE setSort NOTIFY sortChanged)

			//Specify pagination
			Q_PROPERTY(APagination *pagination READ pagination)
			//Specify filters parametres
			Q_PROPERTY(QVariantMap filters READ filters WRITE setFilters NOTIFY filtersChanged)
			//Specify fields parameter
			Q_PROPERTY(QStringList fields READ fields WRITE setFields NOTIFY fieldsChanged)
			//Specify expand parameter
			Q_PROPERTY(QStringList expand READ expand WRITE setExpand NOTIFY expandChanged)
			//Specify Accept header for application/json or application/xml
			Q_PROPERTY(QByteArray accept READ accept WRITE setAccept NOTIFY acceptChanged)

			//ѕараметры идут как пара ключь - значение
			Q_PROPERTY(QVariantMap parameters READ parameters WRITE setParameters NOTIFY parametersChanged)


			//identify column name, role, last fetched detail and detailModel
			Q_PROPERTY(QString idField READ idField WRITE setIdField NOTIFY idFieldChanged)
			Q_PROPERTY(bool enableDetailsCaching READ enableDetailsCaching WRITE setEnableDetailsCaching NOTIFY enableDetailsCachingChanged)
			Q_PROPERTY(int idFieldRole READ idFieldRole)
			Q_PROPERTY(QString fetchDetailLastId READ fetchDetailLastId)
			Q_PROPERTY(ADetailsModel *detailsModel READ detailsModel)
			Q_PROPERTY(QQmlPropertyMap *details READ details CONSTANT)

			//load status and result code
			Q_PROPERTY(LoadingStatus loadingStatus READ loadingStatus WRITE setLoadingStatus NOTIFY loadingStatusChanged)
			Q_PROPERTY(QString loadingErrorString READ loadingErrorString WRITE setLoadingErrorString NOTIFY loadingErrorStringChanged)
			Q_PROPERTY(QNetworkReply::NetworkError loadingErrorCode READ loadingErrorCode WRITE setLoadingErrorCode NOTIFY loadingErrorCodeChanged)
			Q_PROPERTY(int count READ count NOTIFY countChanged)

			//current status of model
			enum LoadingStatus 
			{
				Idle,
				IdleDetails,
				RequestToReload,
				FullReloadProcessing,
				LoadMoreProcessing,
				LoadDetailsProcessing,
				Error
			};

		Q_ENUMS(LoadingStatus)

		
		static void declareQML();


		//Properties GET methods
		QStringList sort() const;
		LoadingStatus loadingStatus() const;
		QVariantMap filters() const;
		QString loadingErrorString() const;
		QNetworkReply::NetworkError loadingErrorCode() const;
		QStringList fields() const;
		QStringList expand() const;
		QString idField() const;
		int idFieldRole() const;
		QString fetchDetailLastId() const;
		ADetailsModel *detailsModel();
		QQmlPropertyMap *details();
		APagination *pagination();
		QByteArray accept();
		QVariantMap parameters() const;
		int count() const;


		//Overloaded system methdos
		QVariant data(const QModelIndex &index, int role) const;

		bool enableDetailsCaching() const;
		void setEnableDetailsCaching(bool enableDetailsCaching);

	signals:
		//Properties signals
		void countChanged();
		void sortChanged(QStringList sort);
		void loadingStatusChanged(LoadingStatus loadingStatus);
		void filtersChanged(QVariantMap filters);
		void loadingErrorStringChanged(QString loadingErrorString);
		void loadingErrorCodeChanged(QNetworkReply::NetworkError loadingErrorCode);
		void fieldsChanged(QStringList fields);
		void expandChanged(QStringList expand);
		void idFieldChanged(QString idField);
		void acceptChanged(QByteArray accept);
		void apiInstanceChanged(APIBase *apiInstance);
		void enableDetailsCachingChanged(bool enableDetailsCaching);
		void parametersChanged(QVariantMap parameters);

	public slots:
		void reload();
		void fetchDetail(QString id);
		void replyError(QNetworkReply *reply, QNetworkReply::NetworkError error, QString errorString);

		void requestToReload();
		void forceIdle();

		//Overloaded system methdos
		bool canFetchMore(const QModelIndex &parent) const;
		void fetchMore(const QModelIndex &parent);
		int rowCount(const QModelIndex &parent = QModelIndex()) const;

		//Properties public SET methods
		void setSort(QStringList sort);
		void setFilters(QVariantMap filters);
		void setFields(QStringList fields);
		void setExpand(QStringList expand);
		void setIdField(QString idField);
		void setParameters(QVariantMap parameters);

		void setApiInstance(APIBase *apiInstance);

	protected:
		//reimplement this for call specific API method GET list
		virtual QNetworkReply *fetchMoreImpl(const QModelIndex &parent) = 0;
		//reimplement this for call specific API method GET details of record by ID
		virtual QNetworkReply *fetchDetailImpl(const QString &id) = 0;
		//reimplenet this for prepropcessing each item before add it to model
		virtual QVariantMap preProcessItem(const QVariantMap &item) = 0;
		//for parse list, reimplemented in JSON and XML models
		virtual QVariantList getVariantList(const QByteArray &bytes) = 0;
		//for parse details for one element, reimplemented in JSON and XML models
		virtual QVariantMap getVariantMap(const QByteArray &bytes) = 0;
		//API instance for models for one external API service
		APIBase *apiInstance();

		//Update specific headers on updating
		void updateHeadersData(QNetworkReply *reply);

		//Reset model data
		void reset();

		//Auto generate role names by REST keys
		void generateRoleNames();
		void generateDetailsRoleNames(const QVariantMap &item);

		//Items management
		AItem createItem(const QVariantMap &value);
		void updateItem(const QVariantMap &value);
		AItem findItemById(const QString &id);
		void append(const AItem &item);

		QHash<int, QByteArray> roleNames() const;
		QHash<int, QByteArray> detailsRoleNames() const;

	protected slots:
		//Properties protected SET methods
		void fetchMoreFinished();
		void fetchDetailFinished();
		void setLoadingStatus(LoadingStatus loadingStatus);
		void setAccept(QString accept);
		void setLoadingErrorString(QString loadingErrorString);
		void setLoadingErrorCode(QNetworkReply::NetworkError loadingErrorCode);

	private:

		QHash<int, QByteArray> mRoleNames;
		int mRoleNamesIndex;
		bool mDetailRoleNamesGenerated;
		QList<AItem> mItems;
		QStringList mFields;
		QStringList mExpand;
		QString mIdField;
		QStringList mSort;
		LoadingStatus mLoadingStatus;
		QVariantMap mFilters;
		QVariantMap mParameters;
		QString mLoadingErrorString;
		QNetworkReply::NetworkError mLoadingErrorCode;
		QString mFetchDetailLastId;
		ADetailsModel mDetailsModel;
		QQmlPropertyMap mDetails;
		APagination mPagination;
		APIBase *mApiInstance;
		bool mEnableDetailsCaching;
	};

}
