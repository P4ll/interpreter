#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

const int n = 51;
const int m = 7;

bool haveStrStr(string str1, string str2) {
	for (int i = 0; i < str1.size(); ++i) {
		int j;
		for (j = 0; j < str2.size() && i + j < str1.size(); ++j) {
			if (str1[i + j] != str2[j])
				break;
		}
		if (j == str2.size()) {
			if (i + j == str1.size()) {
				return true;
			}
			if (str1[i + j] == 'y' || str1[i + j] == 'w' || str1[i + j] == 'u') {
				return true;
			}
		}
	}
	return false;
}

string replaceAlpha(string a) {
	string out = "";
	for (int i = 0; i < a.size(); i++) {
		string alp = "a" + to_string(i + 1);
		if (a[i] == '0')
			out += "-" + alp;
		else
			out += alp;
	}
	return out;
}

string encodeInpData(string inp[][m]) {
	string out = "";
	const int jWithData = 5;
	for (int i = 1; i <= 31; ++i) {
		string y = "y" + to_string(i);
		out += y + " = ";
		for (int j = 0; j < n; ++j) {
			if (haveStrStr(inp[j][jWithData], y)) {
				string alpha = replaceAlpha(inp[j][1]);
				out += alpha;
				out += inp[j][4];
				out += " V ";
			}
		}
		out += ";\n";
	}
	return out;
}

string encodeFWShift(string inp[][m]) {
	string out = "";
	const int jWithData = 6;
	for (int i = 1; i <= 4; ++i) {
		string y = "w" + to_string(i);
		out += y + " = ";
		for (int j = 0; j < n; ++j) {
			if (haveStrStr(inp[j][jWithData], y)) {
				string alpha = replaceAlpha(inp[j][1]);
				out += alpha;
				out += inp[j][4];
				out += " V ";
			}
		}
		out += ";\n";
	}
	return out;
}

string encodeFUShift(string inp[][m]) {
	string out = "";
	const int jWithData = 6;
	for (int i = 1; i <= 4; ++i) {
		string y = "u" + to_string(i);
		out += y + " = ";
		for (int j = 0; j < n; ++j) {
			if (haveStrStr(inp[j][jWithData], y)) {
				string alpha = replaceAlpha(inp[j][1]);
				out += alpha;
				out += inp[j][4];
				out += " V ";
			}
		}
		out += ";\n";
	}
	return out;
}

int main() {
	string inp[n][m];
	freopen("inp.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> inp[i][j];
		}
	}
	string out = encodeInpData(inp);
	string w = encodeFWShift(inp);
	string u = encodeFUShift(inp);
	cout << out << "\n" << w << "\n" << u;
	return 0;
}