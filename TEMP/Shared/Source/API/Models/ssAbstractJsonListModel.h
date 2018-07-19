#pragma once
#include <QNetworkReply>

#include "ssBaseListModel.h"
///----------------------------------------------------------------------------


namespace API
{
	///----------------------------------------------------------------------------






	 ///---------------------------------------------------------------------------
	///
	/// Абстрактная модель данных
	/// 
	///
	///----------------------------------------------------------------------------
	class AAbstractJsonListModel 
		: 
			public ABaseListModel
	{
		Q_OBJECT
	public:
		explicit AAbstractJsonListModel(QObject *parent = 0);

	protected:

		//for get list
		virtual QVariantList getVariantList(const QByteArray &bytes);
		//for get details for one element
		virtual QVariantMap getVariantMap(const QByteArray &bytes);
	};

}
