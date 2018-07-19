#pragma once
#include <QtQml>
#include "ssAbstractJsonListModel.h"
#include "ssRequests.h"
///----------------------------------------------------------------------------


namespace API
{
	///----------------------------------------------------------------------------






	 ///---------------------------------------------------------------------------
	///
	/// Основная модель списка данных
	/// 
	///
	///----------------------------------------------------------------------------
	class AJsonListModel 
		: 
			public AAbstractJsonListModel
	{
		Q_OBJECT

	public:
		explicit AJsonListModel(QObject *parent = 0);

		Q_PROPERTY(ARequests *requests READ requests)

		static void declareQML()
		{
			AAbstractJsonListModel::declareQML();
			qmlRegisterType<ARequests>("com.sla.requests", 1, 0, "ARequests");
			qmlRegisterType<AJsonListModel>("com.sla.jsonlistmodel", 1, 0, "AJsonListModel");
		}

		ARequests *requests()
		{
			return &mRequests;
		}

	protected:
		QNetworkReply *fetchMoreImpl(const QModelIndex &parent) override;
		QNetworkReply *fetchDetailImpl(const QString &id) override;
		QVariantMap preProcessItem(const QVariantMap &item) override;

		ARequests mRequests;
	};
}
