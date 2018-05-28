#pragma once

#include <vector>
#include <ctype.h>

class ExpPart {
public:
	bool isAnyValue = false;
	char letter;
	int number;
	bool isNegative;
	ExpPart();
	ExpPart(char sym, int num);
	ExpPart(char let, int num, bool isNeg);
	char getBinDigit();
	bool operator < (ExpPart &p2) const;
};

class MultiExpression {
private:
	std::vector<ExpPart> expression;
public:
	MultiExpression(std::string str);
	MultiExpression();
	MultiExpression(int count);
	ExpPart getExPart(int id);
	void transformToTripleMatForm();
};