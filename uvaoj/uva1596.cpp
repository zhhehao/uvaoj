#include <iostream>
#include <sstream>
#include <string>
#include <map>
using namespace std;

#define OUTPUT {cout << line << endl; jump(); nobug = false; break;}
#define ARGU string& s, map<string, int>& m

int dindex(ARGU);
int avalue(ARGU);
void jump(void);
int tonum(const string& s);
string tostr(const int& n);

int main() {
	string s;
	for (;;) {
		getline(cin, s);
		if (s == ".") break;
		map<string, int> m;
		int line = 0;
		bool nobug = true;
		do {
			line++;
			int pos = s.find('=');
			if (pos == -1) {
				int index = dindex(s, m);
				if (m.count(s)) OUTPUT
				m[s] = index;
			}
			else {
				string left, right;
				left = s.substr(0, pos);
				right = s.substr(pos+1);
				int lti, rti;
				lti = avalue(left, m);
				if (lti == -1) OUTPUT 
				if (right.find('[') == -1) {
					m[left] = tonum(right);
					continue;
				}
				rti = avalue(right, m);
				if (rti == -1 or rti == -2) OUTPUT
				m[left]=rti;
			}
		} while (getline(cin, s) && s != "."); 
		if (nobug)
			cout << "0\n";
		m.clear();
	}
	return 0;
}

int dindex(ARGU) {
	string str1, str2;
	int pos = s.find('[');
	str1 = s.substr(0, pos+1) + "]";
	str2 = s.substr(pos+1, s.size()-str1.size());
	s = str1;
	return tonum(str2);
}

int avalue(ARGU) {
	string str1, str2;
	int pos = s.find('[');
	str1 = s.substr(0, pos+1) + "]";
	str2 = s.substr(pos+1, s.size()-str1.size());
	bool isnum;
	if (str2.find('[') == -1)
		isnum = true;
	else
		isnum = false;
	if (isnum) {
		if (m.count(str1)) {
			if (tonum(str2) < m[str1]) {
				if (m.count(s)) {
					return m[s];
				}
				else
					return -2;
			}
			else
				return -1;
		}
		else
			return -1;
	}
	else {
		int rnum = avalue(str2, m);
		if (rnum == -1 || rnum == -2) 
			return -1;
		else {
			if (m.count(str1)) {
				if (rnum < m[str1]) {
					s = str1.substr(0, str1.size()-1) + tostr(rnum) + "]";
					if (m.count(s)) {
						return m[s];
					}
					else 
						return -2;
				}
				else
					return -1;
			}
			else
				return -1;
		}		
	}
}

void jump(void) {
	string s;
	while (getline(cin, s) && s != ".")
		;
}

int tonum(const string& s) {
	stringstream ss(s);
	int num;
	ss >> num;
	return num;
}

string tostr(const int& n) {
	stringstream ss;
	ss << n;
	string str;
	ss >> str;
	return str;
}
