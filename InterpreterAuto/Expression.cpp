#include <algorithm>
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

bool ExpPart::operator<(const ExpPart & p) const
{
	return letter < p.letter || letter == p.letter && number < p.number;
}

bool ExpPart::operator==(ExpPart &p2) const
{
	return letter == p2.letter && number == p2.number && isNegative == p2.isNegative;
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
	bool alphas[COUNT_ALPHA + 1] = {};
	bool xx[COUNT_X + 1] = {};
	for (int i = 0; i < expression.size(); ++i) {
		if (expression[i].letter == 'a') {
			alphas[expression[i].number] = true;
		}
	}
	for (int i = 0; i < expression.size(); ++i) {
		if (expression[i].letter == 'x') {
			xx[expression[i].number] = true;
		}
	}
	for (int i = 1; i <= COUNT_ALPHA; ++i) {
		if (!alphas[i])
			expression.push_back(ExpPart('a', i));
	}
	for (int i = 1; i <= COUNT_X; ++i) {
		if (!xx[i])
			expression.push_back(ExpPart('x', i));
	}
	std::sort(expression.begin(), expression.end());
}

int MultiExpression::size()
{
	return expression.size();
}

ExpPart MultiExpression::operator[](int id) const
{
	return expression[id];
}

bool MultiExpression::operator==(MultiExpression ex) const
{
	for (int i = 0, j = 0; i < expression.size() && j < ex.size(); ++j, ++i) {
		if (expression[i].letter != ex.expression[j].letter || expression[i].number != ex.expression[j].number) {
			if (ex.size() > expression.size())
				i--;
			else
				j--;
		}

		if (expression[i].isAnyValue || ex[j].isAnyValue) {
			continue;
		}
		if (!(expression[i] == ex[j])) {
			return false;
		}
	}
	return true;
}

void MultiExpression::trasformByBinaryString(std::string binStr)
{
	expression.resize(COUNT_ALPHA + COUNT_X);
	int i;
	for (i = 0; i < COUNT_ALPHA; ++i) {
		expression[i].letter = 'a';
		expression[i].number = i + 1;
		if (binStr[i] == '0')
			expression[i].isNegative = true;
		else
			expression[i].isNegative = false;
	}
	for (; i < COUNT_ALPHA + COUNT_X; ++i) {
		expression[i].letter = 'x';
		expression[i].number = i - COUNT_ALPHA + 1;
		if (binStr[i] == '0')
			expression[i].isNegative = true;
		else
			expression[i].isNegative = false;
	}
}

bool MultiExpression::isZeroState() const
{
	for (int i = 0; i < COUNT_ALPHA; ++i) {
		if (!expression[i].isNegative)
			return false;
	}
	return true;
}

void MultiExpression::setStateByBinStr(std::string str)
{
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] == '0')
			expression[i].isNegative = true;
		else
			expression[i].isNegative = false;
	}
}

std::string MultiExpression::getStateInBin()
{
	std::string out = "";
	for (int i = 0; i < COUNT_ALPHA; ++i) {
		if (expression[i].isNegative)
			out += '0';
		else
			out += '1';
	}
	return out;
}

bool MultiExpression::calculateByBinStr(std::string str)
{
	for (int i = 0; i < expression.size(); ++i) {
		int bitPos = expression[i].number - 1;
		if (expression[i].letter == 'x')
			bitPos += COUNT_ALPHA;
		bool bitVal = str[bitPos] == '1' ? 1 : 0;
		if (!expression[i].isNegative != bitVal)
			return 0;
	}
	return 1;
}
