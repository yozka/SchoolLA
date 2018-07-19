#include "ssBaseListModel.h"
#include <QtQml>
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
ABaseListModel :: ABaseListModel(QObject *parent) 
	: 
		QAbstractListModel(parent), 
		mRoleNamesIndex(0),
		mDetailRoleNamesGenerated(false), 
		mSort("-id"), 
		mLoadingStatus(LoadingStatus::Idle), 
		mApiInstance(nullptr), 
		mEnableDetailsCaching(true)
{

}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel::declareQML()
{
    qRegisterMetaType<ADetailsModel*>("ADetailsModel*");
    qmlRegisterType<APagination>("com.sla.pagination", 1, 0, "APagination");
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel :: reload()
{
    setLoadingStatus(LoadingStatus::RequestToReload);
    this->fetchMore(QModelIndex());
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
bool ABaseListModel :: canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    switch(mPagination.policy()) 
	{
    case APagination::PageNumber:
		{
			if (mPagination.currentPage() < mPagination.pageCount()) 
			{
				return true;
			} 
			return false;
		}

    case APagination::LimitOffset:
    case APagination::Cursor:
		{
			if (rowCount() < mPagination.totalCount())
			{
				return true;
			}
			return false;
		}

    case APagination::None:
        return false;

    case  APagination::Infinity:
        return true;
    default:
		break;
    }
	return false;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel :: fetchMore(const QModelIndex &parent)
{
    Q_UNUSED(parent)

    switch (loadingStatus()) 
	{
    case LoadingStatus::RequestToReload:
		{
			mPagination.setCurrentPage(0);
			mPagination.setOffset(0);
			mPagination.setCursorValue(0);
			setLoadingStatus(LoadingStatus::FullReloadProcessing);
			break;
		}
    case LoadingStatus::Idle:
    case LoadingStatus::IdleDetails:
		{
			setLoadingStatus(LoadingStatus::LoadMoreProcessing);
			break;
		}
    default:
        return;
    }

    switch(mPagination.policy()) 
	{
    case APagination::PageNumber: 
		{
			const int nextPage = mPagination.currentPage() + 1;
			mPagination.setCurrentPage(nextPage);
			break;
		}

    case APagination::LimitOffset: 
		{
			const int offset = mPagination.offset() + mPagination.limit();
			mPagination.setOffset(offset);
			break;
		}

    case APagination::Cursor: 
		{
			QString cursor = 0;
			if (!mItems.isEmpty()) 
			{
				cursor = mItems.last().id();
			}
			mPagination.setCursorValue(cursor);
			break;
		}
    default:
        break;
    }

    QNetworkReply *reply = fetchMoreImpl(parent);
    connect(reply, SIGNAL(finished()), this, SLOT(fetchMoreFinished()));
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel :: fetchMoreFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (apiInstance()->checkReplyIsError(reply) || !reply->isFinished()) 
	{
        return;
    }

    if (this->loadingStatus() == LoadingStatus::Idle) 
	{
        return;
    }

    updateHeadersData(reply);

    QVariantList values = getVariantList(reply->readAll());

    //prepare vars
    int insertFrom = rowCount();
    int insertCount = rowCount()+values.count();

    //check if we need to full reload
    if (this->loadingStatus() == LoadingStatus::FullReloadProcessing) 
	{
        reset();
        insertFrom = rowCount();
        insertCount = values.count();
    }

    //check for assertion or empty data
    if (insertCount < insertFrom) 
	{ 
		insertCount = insertFrom; 
	}

    if (insertCount == 0) 
	{
        setLoadingStatus(LoadingStatus::Error);
        emit countChanged();
        qDebug() << "Nothing to insert! Please check your parser!" << count() << loadingStatus();
        return;
    }

    //append rows to model
    beginInsertRows(this->index(rowCount(), 0), insertFrom, insertCount - 1);

    QListIterator<QVariant> i(values);
    while (i.hasNext()) 
	{
        AItem item = createItem(i.next().toMap());
        append(item);
    }

    //get all role names
    generateRoleNames();

    endInsertRows();

    setLoadingStatus(LoadingStatus::Idle);

    emit countChanged();
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel :: fetchDetail(QString id)
{
    mFetchDetailLastId = id;
    AItem item = findItemById(id);

    if (!item.isValid()) 
	{
        qWarning() << QString("No item with id %1").arg(id);
        return;
    }

    if (enableDetailsCaching() && item.isUpdated())
	{
        return;
    }

    switch (loadingStatus()) 
	{
		case LoadingStatus::Idle:
		case LoadingStatus::IdleDetails:
		{
			setLoadingStatus(LoadingStatus::LoadDetailsProcessing);
			break;
		}
		default:
			return;
    }

    mDetailsModel.invalidateModel();

    // clean up the details model (QQmlPropertyMap)
    for (const QString &key : mDetails.keys()) 
	{
        mDetails.clear(key);
    }

    QNetworkReply *reply = fetchDetailImpl(id);
    connect(reply, SIGNAL(finished()), this, SLOT(fetchDetailFinished()));
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel :: fetchDetailFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (apiInstance()->checkReplyIsError(reply) || !reply->isFinished()) 
	{
        return;
    }

    if (this->loadingStatus() == LoadingStatus::Idle) 
	{
        return;
    }

    QVariantMap item = preProcessItem(getVariantMap(reply->readAll()));

    updateItem(item);

    generateDetailsRoleNames(item);

    detailsModel()->setSourceModel(this);

    // fill up the details model (QQmlPropertyMap)
    QMapIterator<QString, QVariant> i(item);
    while (i.hasNext()) 
	{
        i.next();
        mDetails.insert(i.key(), i.value());
    }

    setLoadingStatus(LoadingStatus::IdleDetails);
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel :: setLoadingStatus(ABaseListModel::LoadingStatus loadingStatus)
{
    if (mLoadingStatus == loadingStatus) 
	{
        return;
    }

    mLoadingStatus = loadingStatus;
    emit loadingStatusChanged(loadingStatus);
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel :: setAccept(QString accept)
{
    apiInstance()->setAccept(accept);
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel :: setLoadingErrorString(QString loadingErrorString)
{
    if (mLoadingErrorString == loadingErrorString)
        return;

    mLoadingErrorString = loadingErrorString;
    emit loadingErrorStringChanged(loadingErrorString);
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel :: setLoadingErrorCode(QNetworkReply::NetworkError loadingErrorCode)
{
    if (mLoadingErrorCode == loadingErrorCode)
        return;

    mLoadingErrorCode = loadingErrorCode;
    emit loadingErrorCodeChanged(loadingErrorCode);
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
bool ABaseListModel :: enableDetailsCaching() const
{
    return mEnableDetailsCaching;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel::setEnableDetailsCaching(bool enableDetailsCaching)
{
    if (mEnableDetailsCaching == enableDetailsCaching) 
	{
        return;
    }

    mEnableDetailsCaching = enableDetailsCaching;
    emit enableDetailsCachingChanged(enableDetailsCaching);
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel::replyError(QNetworkReply *reply, QNetworkReply::NetworkError error, QString errorString)
{
    Q_UNUSED(reply)
    setLoadingErrorCode(error);
    setLoadingErrorString(errorString);
    setLoadingStatus(LoadingStatus::Error);
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
AItem ABaseListModel :: createItem(const QVariantMap &value)
{
    return AItem(preProcessItem(value),idField());
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
AItem ABaseListModel :: findItemById(const QString &id)
{
    QListIterator<AItem> i(mItems);
    while (i.hasNext()) 
	{
        AItem item = i.next();
        if (item.id() == id) 
		{
            return item;
        }
    }

    return AItem();
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel :: updateItem(const QVariantMap &value)
{
    const QString id = fetchDetailLastId();
    AItem item = findItemById(id);

    if (!item.isValid()) 
	{
        qWarning() << QString("No item with id %1").arg(id);
        return;
    }

    const int row = mItems.indexOf(item);
    item.update(value);
    mItems.replace(row, item);
    emit dataChanged(index(row),index(row));
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
QVariant ABaseListModel :: data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mItems.count()) 
	{
        qDebug() << "Row not found" << index.row();
        return QVariant();
    }

    const AItem item = mItems.at(index.row());
    return item.value(mRoleNames[role]);
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
QStringList ABaseListModel :: sort() const
{
    return mSort;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
ABaseListModel :: LoadingStatus ABaseListModel::loadingStatus() const
{
    return mLoadingStatus;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
QVariantMap ABaseListModel :: filters() const
{
    return mFilters;
}
///----------------------------------------------------------------------------




 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
QVariantMap ABaseListModel::parameters() const
{
	return mParameters;
}
///----------------------------------------------------------------------------





 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
QString ABaseListModel :: loadingErrorString() const
{
    return mLoadingErrorString;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
QNetworkReply::NetworkError ABaseListModel :: loadingErrorCode() const
{
    return mLoadingErrorCode;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
QStringList ABaseListModel :: fields() const
{
    return mFields;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
QStringList ABaseListModel :: expand() const
{
    return mExpand;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
QString ABaseListModel::idField() const
{
    return mIdField;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
int ABaseListModel :: idFieldRole() const
{
    QByteArray obj;
    obj.append(idField());
    return mRoleNames.key(obj);
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
QString ABaseListModel :: fetchDetailLastId() const
{
    return mFetchDetailLastId;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
ADetailsModel *ABaseListModel :: detailsModel()
{
    return &mDetailsModel;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
QQmlPropertyMap *ABaseListModel :: details()
{
    return &mDetails;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
APagination *ABaseListModel :: pagination()
{
    return &mPagination;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
QByteArray ABaseListModel::accept()
{
    return apiInstance()->accept();
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
int ABaseListModel::count() const
{
    return mItems.count();
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
QHash<int, QByteArray> ABaseListModel :: roleNames() const
{
    return mRoleNames;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
QHash<int, QByteArray> ABaseListModel :: detailsRoleNames() const
{
    return mRoleNames;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel :: updateHeadersData(QNetworkReply *reply)
{
    //update headers data
    QByteArray currentPage;
    currentPage.append(mPagination.currentPageHeader());
    QByteArray totalCount;
    totalCount.append(mPagination.totalCountHeader());
    QByteArray pageCount;
    pageCount.append(mPagination.pageCountHeader());

    mPagination.setCurrentPage(reply->rawHeader(currentPage).toInt());
    mPagination.setTotalCount(reply->rawHeader(totalCount).toInt());
    mPagination.setPageCount(reply->rawHeader(pageCount).toInt());
    reply->deleteLater();

    //todo other headers (limit offset and cursor)
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel :: reset()
{
    beginResetModel();
    mItems.clear();
    endResetModel();
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel :: append(const AItem &item)
{
    mItems.append(item);
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel :: generateRoleNames()
{
    if (mRoleNamesIndex > 0) 
	{
        return;
    }

    AItem item = mItems[0];

	const QStringList keys = item.keys();

    if (rowCount() > 0) 
	{
        foreach (QString key, keys) 
		{
            QByteArray k;
            k.append(key);
            if (!mRoleNames.key(k)) 
			{
                mRoleNamesIndex++;
                mRoleNames[mRoleNamesIndex] = k;
            }
        }
    }
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel :: generateDetailsRoleNames(const QVariantMap &item)
{
    if (mDetailRoleNamesGenerated) 
	{ 
		return; 
	}

    const QStringList keys = item.keys();

    if (rowCount() > 0) 
	{
        foreach (QString key, keys) 
		{
            QByteArray k = key.toUtf8();
            if (!mRoleNames.key(k)) 
			{
                mRoleNamesIndex++;
                mRoleNames[mRoleNamesIndex] = k;
            }
        }
    }

    mDetailRoleNamesGenerated = true;
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
int ABaseListModel :: rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mItems.count();
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel :: requestToReload() 
{
    setLoadingStatus(LoadingStatus::RequestToReload);
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel::forceIdle() 
{
    setLoadingStatus(LoadingStatus::Idle);
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel :: setSort(QStringList sort)
{
    if (mSort == sort)
        return;

    mSort = sort;
    emit sortChanged(sort);
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel :: setFilters(QVariantMap filters)
{
    if (mFilters == filters)
        return;

    mFilters = filters;
    emit filtersChanged(filters);
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel :: setFields(QStringList fields)
{
    if (mFields == fields)
        return;

    mFields = fields;
    emit fieldsChanged(fields);
}
///----------------------------------------------------------------------------





 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel :: setParameters(QVariantMap parameters)
{
	if (mParameters == parameters)
		return;

	mParameters = parameters;
	emit parametersChanged(parameters);
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel::setExpand(QStringList expand)
{
    if (mExpand == expand)
        return;

    mExpand = expand;
    emit expandChanged(expand);
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel::setIdField(QString idField)
{
    if (mIdField == idField)
        return;

    mIdField = idField;
    emit idFieldChanged(idField);
}
///----------------------------------------------------------------------------






 ///---------------------------------------------------------------------------
///
/// 
/// 
///
///----------------------------------------------------------------------------
void ABaseListModel :: setApiInstance(APIBase *apiInstance)
{
    if (mApiInstance == apiInstance)
        return;

    mApiInstance = apiInstance;

    mApiInstance->setAccept(accept());
    connect(mApiInstance,SIGNAL(replyError(QNetworkReply *, QNetworkReply::NetworkError, QString)),
            this, SLOT(replyError(QNetworkReply *, QNetworkReply::NetworkError, QString)));

    emit apiInstanceChanged(apiInstance);
}

APIBase *ABaseListModel::apiInstance()
{
    if (mApiInstance == nullptr) 
	{
        return new APIBase(this);
    }
    return mApiInstance;
}
