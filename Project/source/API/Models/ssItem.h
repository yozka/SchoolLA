#pragma once
#include <QVariantMap>
///----------------------------------------------------------------------------


namespace API
{
	///----------------------------------------------------------------------------






	 ///---------------------------------------------------------------------------
	///
	/// ќдин элемент данных
	/// 
	///
	///----------------------------------------------------------------------------
	class AItem 
	{
	public:
		AItem();
		explicit AItem(const QVariantMap &object, const QString &idField);
		QVariant value(const QString &key) const;
		QStringList keys() const;
		QString id() const;
		bool isUpdated() const;
		bool isValid() const;

		void update(const QVariantMap &value);

		bool operator==(const AItem &other);
	private:
		QVariantMap mObject;
		QString mIdField;
		bool mIsUpdated;
		bool mIsValid;
	};

}
