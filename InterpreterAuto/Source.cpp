#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <chrono>
#include <set>
#include <bitset>
#include <stdlib.h>

#include "Expression.h"
#include "Settings.h"

using namespace std;

vector<vector<MultiExpression>> wExp;
vector<vector<MultiExpression>> yExp;
vector<vector<MultiExpression>> uExp;

vector<vector<MultiExpression>> getData(string fileName);
void tripleMatrix(string stateStr, string inpStr);
pair<string, bool> getTripleMatrixAns(string stateStr, string inpStr);
void logicExpressions(string stateStr, string inpStr);
pair<string, bool> getLogicExpressionsAns(string stateStr, string inpStr);
string outputYData(bool currentOutput[]);
void normalMode();
void testMode();
void testMode2();
void trasformAllDataForTrMatrix();
string getStartStateInBinStr();

struct TestTable {
	string strs[COUNT_COLS_TEST_TABLE];

	bool operator<(const TestTable &t) const {
		for (int i = 0; i < COUNT_COLS_TEST_TABLE; ++i) {
			if (strs[i] == t.strs[i])
				continue;
			if (strs[i] < t.strs[i])
				return true;
			else
				return false;
		}
	}

	bool operator==(const TestTable &t) const {
		for (int i = 0; i < COUNT_COLS_TEST_TABLE; ++i) {
			if (strs[i] != t.strs[i])
				return false;
		}
		return true;
	}
};

int main() {
	ios::sync_with_stdio(0);
	wExp = getData("w.txt");
	yExp = getData("y.txt");
	uExp = getData("u.txt");

	normalMode();
	//testMode2();
	return 0;
}

void normalMode() {
	ifstream inputData("input.txt");
	int workMode;
	string startX;

	inputData >> workMode >> startX;

	inputData.close();

	string startState = getStartStateInBinStr();

	chrono::high_resolution_clock::time_point begTime = chrono::high_resolution_clock::now();
	switch (workMode) {
	case 1:
		trasformAllDataForTrMatrix();
		tripleMatrix(startState, startX);
		break;
	case 2:
		logicExpressions(startState, startX);
		break;
	default:
		cout << "Wrong type";
		break;
	}
	chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
	chrono::duration<double >elapsedTime = chrono::duration_cast< chrono::duration<double> >(endTime - begTime);
	cout << "Time: " << elapsedTime.count() << " sec";
}

void testMode() {
	set<TestTable> testTable;
	ifstream inpTable("table.txt");
	while (!inpTable.eof()) {
		TestTable t;
		for (int i = 0; i < COUNT_COLS_TEST_TABLE && cin >> t.strs[i]; ++i);
		testTable.insert(t);
	}
	inpTable.close();
	bitset<COUNT_X> xValue;
	int targetValue = 1 << (COUNT_X + 1) - 1;
	int currentValue = 0;
	while (currentValue != targetValue) {
		// запуск с этим получаем строки
		++currentValue;
		xValue = currentValue;
	}
}

void testMode2() {
	int type = 2;
	if (type == 1)
		trasformAllDataForTrMatrix();
	ofstream badRes("badResultsLogEx.txt", ios_base::app);
	ofstream goodRes("goodResultsLogEx.txt", ios_base::app);
	bitset<COUNT_X> xValue;
	int targetValue = 1 << (COUNT_X + 1) - 1;
	int currentValue = 0;
	string startState = getStartStateInBinStr();
	while (currentValue != targetValue) {
		pair<string, bool> badTest;
		switch (type) {
		case 1:
			badTest = getTripleMatrixAns(startState, xValue.to_string());
			break;
		case 2:
			badTest = getLogicExpressionsAns(startState, xValue.to_string());
			break;
		default:
			cout << "Wrong number";
			break;
		}
		if (badTest.second) {
			badRes << xValue << endl;
			badRes << badTest.first << "\n";
		}
		else {
			goodRes << xValue << endl;
			goodRes << badTest.first << "\n";
		}
		if (currentValue % 1000 == 0)
			cout << currentValue << endl;
		++currentValue;
		xValue = currentValue;
	}
	badRes.close();
	goodRes.close();
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

void trasformAllDataForTrMatrix() {
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
}

pair<string, bool> getTripleMatrixAns(string stateStr, string inpStr) {
	string outputData = "";
	MultiExpression startExp;
	startExp.trasformByBinaryString(stateStr + inpStr);
	set<string> prevStates;
	prevStates.insert(stateStr);
	int countMoves = 0;
	do {
		bool currentOutput[COUNT_Y] = {};
		for (int i = 0; i < wExp.size(); ++i) {
			for (int j = 0; j < wExp[i].size(); ++j) {
				if (wExp[i][j] == startExp) {
					stateStr[i] = '1';
					break;
				}
			}
		}
		for (int i = 0; i < uExp.size(); ++i) {
			for (int j = 0; j < uExp[i].size(); ++j) {
				if (uExp[i][j] == startExp) {
					stateStr[i] = '0';
					break;
				}
			}
		}
		for (int i = 0; i < yExp.size(); ++i) {
			for (int j = 0; j < yExp[i].size(); ++j) {
				if (startExp == yExp[i][j]) {
					currentOutput[i] = true;
					break;
				}
			}
		}
		outputData += "From " + startExp.getStateInBin() + " to " + stateStr + "\n";
		outputData += outputYData(currentOutput);
		bool testCrash = false;
		if (!prevStates.count(stateStr))
			prevStates.insert(stateStr);
		else {
			testCrash = 1;
		}
		startExp.setStateByBinStr(stateStr);
		if (!startExp.isZeroState() && testCrash || testCrash && prevStates.size() == 1) {
			return make_pair(outputData, 1);
			//cout << "crash\n";
			//break;
		}
		++countMoves;
	} while (!startExp.isZeroState());
	outputData += "Count states: " + to_string(countMoves) + "\n";
	return make_pair(outputData, 0);
}

void tripleMatrix(string stateStr, string inpStr) {
	pair<string, bool> t = getTripleMatrixAns(stateStr, inpStr);
	cout << t.first;
	if (t.second)
		cout << "crash" << endl;
}

pair<string, bool> getLogicExpressionsAns(string stateStr, string inpStr) {
	string outputData = "";
	string endState = stateStr;
	string startStr = stateStr + inpStr;
	set<string> prevStates;
	prevStates.insert(stateStr);
	int countMoves = 0;
	do {
		bool currentOutput[COUNT_Y] = {};
		outputData += "From " + stateStr + " to ";
		for (int i = 0; i < wExp.size(); ++i) {
			for (int j = 0; j < wExp[i].size(); ++j) {
				if (wExp[i][j].calculateByBinStr(startStr)) {
					stateStr[i] = '1';
					break;
				}
			}
		}
		for (int i = 0; i < uExp.size(); ++i) {
			for (int j = 0; j < uExp[i].size(); ++j) {
				if (uExp[i][j].calculateByBinStr(startStr)) {
					stateStr[i] = '0';
					break;
				}
			}
		}
		for (int i = 0; i < yExp.size(); ++i) {
			for (int j = 0; j < yExp[i].size(); ++j) {
				if (yExp[i][j].calculateByBinStr(startStr)) {
					currentOutput[i] = true;
				}
			}
		}
		outputData += stateStr + "\n" + outputYData(currentOutput);
		for (int i = 0; i < stateStr.size(); ++i) {
			startStr[i] = stateStr[i];
		}
		bool crash = 0;
		if (!prevStates.count(stateStr))
			prevStates.insert(stateStr);
		else
			crash = 1;
		if (crash && stateStr != endState || crash && prevStates.size() == 1) {
			return make_pair(outputData, 1);
			//break;
		}
		++countMoves;
	} while (stateStr != endState);
	outputData += "Count states: " + to_string(countMoves) + "\n";
	return make_pair(outputData, 0);
}

void logicExpressions(string stateStr, string inpStr) {
	pair<string, bool> t = getLogicExpressionsAns(stateStr, inpStr);
	cout << t.first;
	if (t.second)
		cout << "crash" << endl;
}

string outputYData(bool currentOutput[]) {
	string outputData = "";
	vector<int> a;
	for (int i = 0; i < COUNT_Y; ++i) {
		if (currentOutput[i])
			outputData += "1", a.push_back(i + 1);
		else
			outputData += "0";
	}
	outputData += " = ";
	for (int i = 0; i < a.size(); ++i) {
		outputData += to_string(a[i]);
		if (i + 1 < a.size()) outputData += ", ";
	}
	outputData += "\n";
	return outputData;
}
string getStartStateInBinStr() {
	string startState = "";

	for (int i = 0; i < COUNT_ALPHA; ++i) {
		startState += '0';
	}
	return startState;
}