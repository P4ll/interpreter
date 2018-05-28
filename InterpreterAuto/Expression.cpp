#include "Expression.h"

ExpPart::ExpPart() {
	letter = '*';
	number = 0;
	isNegative = false;
}

ExpPart::ExpPart(char let, int num, bool isNeg)
{
	letter = let;
	number = num;
	isNegative = isNeg;
}

bool ExpPart::isAnySymbol()
{
	if (letter == '*')
		return true;
	else
		return false;
}

MultiExpression::MultiExpression(std::string str)
{
	for (int i = 0; i < str.size(); ++i) {
		ExpPart t;

	}
}

ExpPart MultiExpression::getExPart(int id)
{
	return expression[id];
}
