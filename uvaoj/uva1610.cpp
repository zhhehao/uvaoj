#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;

const int maxn = 500 + 10;

string str[maxn];

int main() {
	int n;
	while (cin >> n) {
		if (n == 0) break;
		int hn = n / 2;
		for (int i = 0; i <= hn; i++) cin >> str[i];
		sort(str, str+hn+1);
		string stmp;
		int remain = hn - 1;
		for (int i = 0; i < remain; i++) {
			cin >> stmp;
			if (stmp >= str[hn]) continue;
			if (stmp >= str[hn-1]) {str[hn] = stmp; continue;}
			int pos = upper_bound(str, str+hn, stmp) - str;
			for (int j = hn; j > pos; j--) str[j] = str[j-1];
			str[pos] = stmp;
		}
		string s1 = str[hn-1], s2 = str[hn];
		int len = max(s1.size(), s2.size());
		for (int i = 0; i < len; i++) {
			if (s1[i] == s2[i]) {
				printf("%c", s1[i]);
				if (i+1 == s1.size()) {
					printf("\n");
					break;
				}
			}
			else {
				if (s2[i]-s1[i] > 1) {
					if (i+1 == s1.size()) {
						printf("%c\n", s1[i]);
						break;
					}
					else {
						printf("%c\n", s1[i]+1);
						break;
					}
				}
				else {
					if (i+1 < s2.size()) {
						if (i+1 == s1.size()) {
							printf("%c\n", s1[i]);
							break;
						}
						else {
							printf("%c\n", s1[i]+1);
							break;
						}
					}
					else {
						printf("%c", s1[i]);
						for (int j = i+1; j < s1.size(); j++) {
							if (s1[j] == 'Z')
								printf("Z");
							else {
								if (j < s1.size()-1) {
									printf("%c", s1[j]+1);
								}
								else {
									printf("%c", s1[j]);
								}
								break;
							}
						}
						printf("\n");
						break;
					}
				}
			}
		}
	}
	return 0;
}
