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
	for (int i = 0; i < str.size(); ) {
		ExpPart t;
		if (isalpha(str[i])) {
			t.letter = str[i];
			++i;
		}
		if (str[i] == '-') {
			t.isNegative = true;
			++i;
		}
		std::string dig = "";
		while (isdigit(str[i])) {
			dig += str[i];
			++i;
		}
		t.number = atoi(dig.c_str());
		expression.push_back(t);
	}
}

ExpPart MultiExpression::getExPart(int id)
{
	return expression[id];
}
