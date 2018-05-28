#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>

#include "Expression.h"
#include "Settings.h"

using namespace std;

vector<vector<MultiExpression>> wExp;
vector<vector<MultiExpression>> yExp;
vector<vector<MultiExpression>> uExp;

vector<vector<MultiExpression>> getData(string fileName);
void tripleMatrix(string stateStr, string inpStr);
void logicExpressions();

int main() {
	ios::sync_with_stdio(0);
	wExp = getData("w.txt");
	yExp = getData("y.txt");
	uExp = getData("u.txt");

	ifstream inputData("input.txt");
	int workMode;
	string startX;

	inputData >> workMode >> startX;

	inputData.close();

	string startState = "";

	for (int i = 0; i < COUNT_ALPHA; ++i) {
		startState += '0';
	}


	switch (workMode) {
	case 1:
		tripleMatrix(startState, startX);
		break;
	case 2:
		logicExpressions();
		break;
	default:
		cout << "Wrong type";
		break;
	}

	return 0;
}

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

void tripleMatrix(string stateStr, string inpStr) {

	for (int i = 0; i < uExp.size(); ++i) {
		for (int j = 0; j < uExp[i].size(); ++j) {
			uExp[i][j].transformToTripleMatForm();
		}
	}
	for (int i = 0; i < wExp.size(); ++i) {
		for (int j = 0; j < wExp[i].size(); ++j) {
			wExp[i][j].transformToTripleMatForm();
		}
	}
	for (int i = 0; i < yExp.size(); ++i) {
		for (int j = 0; j < yExp[i].size(); ++j) {
			yExp[i][j].transformToTripleMatForm();
		}
	}
	MultiExpression startExp;
	startExp.trasformByBinaryString(stateStr + inpStr);
	do {
		bool currentOutput[COUNT_Y] = {};
		for (int i = 0; i < wExp.size(); ++i) {
			for (int j = 0; j < wExp[i].size(); ++j) {
				if (wExp[i][j] == startExp) {
					stateStr[i] = '1';
				}
			}
		}
		for (int i = 0; i < uExp.size(); ++i) {
			for (int j = 0; j < uExp[i].size(); ++j) {
				if (uExp[i][j] == startExp) {
					stateStr[i] = '0';
				}
			}
		}
		for (int i = 0; i < yExp.size(); ++i) {
			for (int j = 0; j < yExp[i].size(); ++j) {
				if (startExp == yExp[i][j]) {
					currentOutput[i] = true;
				}
			}
		}
		cout << "From " + startExp.getStateInBin() + " to " + stateStr + "\n";
		for (int i = 0; i < COUNT_Y; ++i) {
			if (currentOutput[i])
				cout << "1";
			else
				cout << "0";
		}
		cout << "\n";
		startExp.setStateByBinStr(stateStr);
	} while (!startExp.isZeroState());
}

void logicExpressions() {
	/*
		1) держим строку из 1 и 0
		2) пока состояние на 0000 пробегаемся по всем w и u, вычисляя выражение, потом меняем состояние как надо
		3) тоже самое для y
		4) выводим
	*/
}