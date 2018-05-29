#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctype.h>
using namespace std;

const int COUNT_X = 15;

string genBinLine(string data);
void addToPrevTest();

int main() {
	ios::sync_with_stdio(0);
	return 0;
}

string genBinLine(string data) {
	string output;

	output.resize(COUNT_X);
	fill(output.begin(), output.end(), '0');

	for (int i = 0; i < data.size(); ) {
		if (data[i] == 'x') {
			++i;
			bool isNeg = false;
			if (data[i] == '-') {
				isNeg = true;
				++i;
			}
			string numb = "";
			while (isdigit(data[i])) numb += data[i], ++i;
			int n = atoi(numb.c_str()) - 1;
			if (!isNeg)
				output[n] = '1';
		}
		else
			++i;
	}
	return output;
}

void addToPrevTest() {
	ifstream inp("input.txt");
	string data;
	inp >> data;
	inp.close();
	string output = genBinLine(data);
	cout << output;
	ofstream out("prevTests.txt", ios_base::app);
	out << output << "\n";
	out.close();
}

void toTripleMatrix() {
	ifstream inp("input.txt");
	ofstream out("output.txt");
	
	string t = "";
	string output = "";
	while (inp >> t && !inp.eof()) {
		if (t == "V")
			continue;
		output += genBinLine(t);
		output += '\n';
	}
	out << output;
	inp.close();
	out.close();
}