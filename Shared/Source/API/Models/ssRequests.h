#pragma once
#include <QObject>
///----------------------------------------------------------------------------


namespace API
{
	///----------------------------------------------------------------------------






	 ///---------------------------------------------------------------------------
	///
	/// Запрос от сервера
	/// 
	///
	///----------------------------------------------------------------------------
	class ARequests
		:
		public QObject
	{
		Q_OBJECT


	public:
		Q_INVOKABLE explicit ARequests(QObject *parent = 0);

		Q_PROPERTY(QString get READ get WRITE setGet NOTIFY getChanged)
		Q_PROPERTY(QString getDetails READ getDetails WRITE setGetDetails NOTIFY getDetailsChanged)

		
		QString get() const;
		QString getDetails() const;


	signals:

		void getChanged(QString get);
		void getDetailsChanged(QString getDetails);

	public slots:

		void setGet(QString get);
		void setGetDetails(QString getDetails);
		


	private:

		QString mGet;
		QString mGetDetails;
	};

}
