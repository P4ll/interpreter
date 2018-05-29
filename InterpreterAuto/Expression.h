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
	bool operator < (const ExpPart &p) const;
	bool operator == (ExpPart &p2) const;
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
	int size();
	ExpPart operator [] (int id) const;
	bool operator == (MultiExpression ex) const;
	void trasformByBinaryString(std::string binStr);
	bool isZeroState() const;
	void setStateByBinStr(std::string str);
	std::string getStateInBin();
	bool calculateByBinStr(std::string str);
};