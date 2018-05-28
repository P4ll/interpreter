#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>

#include "Expression.h"

using namespace std;

vector<MultiExpression> &getData(string fileName) {
	ifstream input(fileName);

	input.close();
}

int main() {
	//ios::sync_with_stdio(0);
	ifstream input("input.txt");
	string a;
	input >> a;
	input.close();
	return 0;
}