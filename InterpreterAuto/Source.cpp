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
void tripleMatrix();
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

	string startData = "";

	for (int i = 0; i < COUNT_ALPHA; ++i) {
		startData += '0';
	}
	startData += startX;

	switch (workMode) {
	case 1:
		tripleMatrix();
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
// ���������� a41
void tripleMatrix() {
	/*
		1) ����������� ��������� ������, �� ���� ������������������ ���� � �����
		2) ����������� � ���������� ����� w � u, �� ���� �������� �� � ��������� (�� ��� ���������, � *)
		3) ���� ��������� � ��������� ������ �� ������ ����� ����� 0000, ���������� �� ���� �������� � ������ ����� ���� ��������
		4) ���������� �� ���� y, ����� ������ ����� ������ ���������.
	*/
	MultiExpression w[COUNT_W];
	for (int i = 0; i < COUNT_W; ++i) {
		w[i] = MultiExpression(COUNT_ALPHA + COUNT_X);
	}
	MultiExpression u[COUNT_U];
	for (int i = 0; i < COUNT_U; ++i) {
		u[i] = MultiExpression(COUNT_ALPHA + COUNT_X);
	}
	MultiExpression y[COUNT_Y];
	for (int i = 0; i < COUNT_Y; ++i) {
		y[i] = MultiExpression(COUNT_ALPHA + COUNT_X);
	}

	int a = 10;
}

void logicExpressions() {
	/*
		1) ������ ������ �� 1 � 0
		2) ���� ��������� �� 0000 ����������� �� ���� w � u, �������� ���������, ����� ������ ��������� ��� ����
		3) ���� ����� ��� y
		4) �������
	*/
}