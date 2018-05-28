#pragma once

#include <vector>

class ExpPart {
public:
	char letter;
	int number;
	bool isNegative;
	ExpPart();
	ExpPart(char let, int num, bool isNeg);
	bool isAnySymbol();
};

class MultiExpression {
private:
	std::vector<ExpPart> expression;
public:
	MultiExpression(std::string str);
	ExpPart getExPart(int id);
};