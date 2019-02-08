#include <iostream>
#include <string>
#include <vector>
using namespace std;

void getNext(string pattern, vector<int>& next) {
	int len = pattern.size();
	int i = -1;
	next[0] = -1;
	int j = 0;
	while (j < len-1) {
		if (i == -1 || pattern[i] == pattern[j]) {
			i ++;
			j ++;
			next[j] = i;
		} else {
			i = next[i];
		}
	}
	// for (int i = 0; i < pattern.size(); i ++) {
	// 	cout << pattern[i] << ": " << next[i] << endl;
	// }
}

int match(string source, string pattern) {
	int slen = source.size();
	int plen = pattern.size();
	vector<int> next(pattern.size(), 0);
	getNext(pattern, next);
	int i = 0;
	int j = 0;
	while (i < slen && j < plen) {
		if (j == -1 || source[i] == pattern[j]) {
			i ++;
			j ++;
		} else {
			j = next[j];
		}
	}
	if (j == plen) return i-j;
	return -1;
}

int main() {
	string source = "here is an example";
	string pattern = "is";
	cout << match(source, pattern) << endl;

	// vector<int> next(pattern.size(), 0);
	// getNext(pattern, next);
	// cout << pattern.size() << endl;
	// for (int i = 0; i < pattern.size(); i ++) {
	// 	cout << pattern[i] << ": " << next[i] << endl;
	// }
	return 0;
}