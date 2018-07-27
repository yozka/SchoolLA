#include "ssDetailsModel.h"
#include "ssBaseListModel.h"
#include <QDebug>
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
ADetailsModel :: ADetailsModel()
{

}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
///
/// 
///
///----------------------------------------------------------------------------
bool ADetailsModel :: filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    bool ret = false;

	ABaseListModel *sourceModel = static_cast<ABaseListModel *> (this->sourceModel());

    if ( sourceModel != nullptr )
    {
        QModelIndex index = sourceModel->index( source_row, 0, source_parent );
        if ( index.isValid() )
        {
            QString id = sourceModel->data(index, sourceModel->idFieldRole()).toString();
            if (id == sourceModel->fetchDetailLastId()) 
			{
                ret = true;
            }
        }
    }

    return ret;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ADetailsModel :: invalidateModel() 
{ 
	invalidateFilter(); 
}
