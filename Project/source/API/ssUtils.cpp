#include "ssUtils.h"



//добавить в конце строчки сепаратор разделитель
QString API::utils::makeSeparator(const QString &value)
{
	if (value.right(1) != "/")
	{
		return value + "/";
	}
	return value;
}