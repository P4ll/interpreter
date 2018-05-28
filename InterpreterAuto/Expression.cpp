#include "Expression.h"
#include "Settings.h"

ExpPart::ExpPart() {
	letter = 'x';
	number = 0;
	isNegative = false;
}

ExpPart::ExpPart(char sym, int num) {
	letter = sym;
	number = num;
	isNegative = false;
	isAnyValue = true;
}

ExpPart::ExpPart(char let, int num, bool isNeg)
{
	letter = let;
	number = num;
	isNegative = isNeg;
}

char ExpPart::getBinDigit()
{
	return isNegative == false ? '1' : '0';
}

bool ExpPart::operator < (ExpPart &p2) const
{
	if (this->letter == p2.letter)
		return this->number < p2.number;
	else
		this->letter < p2.letter;
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

MultiExpression::MultiExpression()
{

}

MultiExpression::MultiExpression(int count)
{
	expression.resize(count);
}

ExpPart MultiExpression::getExPart(int id)
{
	return expression[id];
}

void MultiExpression::transformToTripleMatForm()
{
}
