#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
#include <chrono>
#include <set>
#include <stdlib.h>

#include "Expression.h"
#include "Settings.h"

using namespace std;

vector<vector<MultiExpression>> wExp;
vector<vector<MultiExpression>> yExp;
vector<vector<MultiExpression>> uExp;

vector<vector<MultiExpression>> getData(string fileName);
void tripleMatrix(string stateStr, string inpStr);
void logicExpressions(string stateStr, string inpStr);
void outputYData(bool currentOutput[]);

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

	chrono::high_resolution_clock::time_point begTime = chrono::high_resolution_clock::now();
	switch (workMode) {
	case 1:
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
	cout << "Time: " << elapsedTime.count();
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
	set<string> prevStates;
	prevStates.insert(stateStr);
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
		outputYData(currentOutput);
		bool testCrash = false;
		if (!prevStates.count(stateStr))
			prevStates.insert(stateStr);
		else {
			testCrash = 1;
		}
		startExp.setStateByBinStr(stateStr);
		if (!startExp.isZeroState() && testCrash) {
			cout << "crash\n";
			break;
		}
	} while (!startExp.isZeroState());
}

void logicExpressions(string stateStr, string inpStr) {
	string endState = stateStr;
	string startStr = stateStr + inpStr;
	set<string> prevStates;
	prevStates.insert(stateStr);
	do {
		bool currentOutput[COUNT_Y] = {};
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
		outputYData(currentOutput);
		for (int i = 0; i < stateStr.size(); ++i) {
			startStr[i] = stateStr[i];
		}
		bool crash = 0;
		if (!prevStates.count(stateStr))
			prevStates.insert(stateStr);
		else
			crash = 1;
		if (crash && stateStr != endState) {
			cout << "crash\n";
			break;
		}
	} while (stateStr != endState);
}

void outputYData(bool currentOutput[]) {
	vector<int> a;
	for (int i = 0; i < COUNT_Y; ++i) {
		if (currentOutput[i])
			cout << "1", a.push_back(i + 1);
		else
			cout << "0";
	}
	cout << " = ";
	for (int i = 0; i < a.size(); ++i) {
		cout << a[i];
		if (i + 1 < a.size()) cout << ", ";
	}
	cout << "\n";
}