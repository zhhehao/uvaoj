#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;

const int maxn = 1000 + 10;
// const int maxn = 500 + 10;

string str[maxn];

int main() {
	int n;
	while (cin >> n) {
		if (n == 0) break;
		for (int i = 0; i < n; i++) cin >> str[i];
		sort(str, str+n);
		string s1 = str[n/2 - 1], s2 = str[n/2];
		if (s1.size() <= s2.size()) {
			for (int i = 0; i < s1.size(); i++) {
				if (s1[i] == s2[i]) {
					printf("%c", s1[i]);
				}
				else {
					if ((i+1) == s1.size()) {
						printf("%c", s1[i]);
					}
					else {
						printf("%c", s1[i]+1);
					}
					break;
				}
			}
			printf("\n");
		}
		else {
			for (int i = 0; i < s2.size(); i++) {
				if (s1[i] == s2[i]) {
					printf("%c", s1[i]);
				}
				else {
					if ((i+1) == s2.size()) {
						if (s2[i]-s1[i] > 1) {
							printf("%c", s1[i]+1);
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
						}
					}
					else {
						printf("%c", s1[i]+1);
					}
					break;
				}
			}
			printf("\n");
		}
	}
	return 0;
}
