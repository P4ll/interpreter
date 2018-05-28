#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>

#include "Expression.h"

using namespace std;

const int COUNT_ALPHA	= 4;
const int COUNT_X		= 15;
const int COUNT_Y		= 25;
const int COUNT_W		= 4;
const int COUNT_U		= 4;

vector<vector<MultiExpression>> getData(string fileName) {
	ifstream input(fileName);

	vector<vector<MultiExpression>> expressions;
	for (int i = 1; !input.eof(); ++i) {
		vector<MultiExpression> line;
		string temp = "";

		while (input >> temp && temp != ";") {
			if (temp == "V")
				continue;
			MultiExpression tExp(temp);
			line.push_back(tExp);
		}

		expressions.push_back(line);
	}
	input.close();
	return expressions;
}

int main() {
	ios::sync_with_stdio(0);
	vector<vector<MultiExpression>> wExp = getData("w.txt");
	vector<vector<MultiExpression>> yExp = getData("y.txt");
	vector<vector<MultiExpression>> uExp = getData("u.txt");

	ifstream inputData("input.txt");
	int workMode;
	string startX;

	inputData >> workMode >> startX;

	inputData.close();

	string startData = "";

	for (int i = 0; i < COUNT_ALPHA; ++i) {
		startData += '0';
	}
	startData += startX;

	return 0;
}