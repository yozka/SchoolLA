#pragma once
#include <QSortFilterProxyModel>
///----------------------------------------------------------------------------


namespace API
{
	///----------------------------------------------------------------------------






	///---------------------------------------------------------------------------
	///
	/// ���� ������� ������
	/// 
	///
	///----------------------------------------------------------------------------
	class ADetailsModel 
		: 
			public QSortFilterProxyModel
	{
		Q_OBJECT
	public:
		ADetailsModel();

		bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const override;
		void invalidateModel();
	};

}
