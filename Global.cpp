#include <string>

bool isFloat(std::string f_str)
{
	int iDot{ 0 };
	for (auto t : f_str)
	{
		if ((t < '0' || t > '9') && ('.' != t))
			return false;
		else if ('.' == t)
			++iDot;
	}
	if (iDot > 1)
		return false;
	else
		return true;
}
