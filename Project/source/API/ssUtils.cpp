#include "ssUtils.h"



//�������� � ����� ������� ��������� �����������
QString API::utils::makeSeparator(const QString &value)
{
	if (value.right(1) != "/")
	{
		return value + "/";
	}
	return value;
}