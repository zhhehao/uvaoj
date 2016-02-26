#include <iostream>
#include <set>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
using namespace std;

void mtain(set<string>& smta);
void usrin(vector<string>& vusr, string& str, set<string>& susr);
string getmta(string str);
void getcontext(string& context);

int main() {
	set<string> smta;
	mtain(smta);
	for (;;) {
		string str;
		getline(cin, str);
		if (str[0] == '*') break;
		set<string> susr;
		vector<string> vusr;
		usrin(vusr, str, susr);
		queue<string> qmta;
		set<string> chemta;
		for (vector<string>::iterator it = vusr.begin()+1; it != vusr.end(); ++it) {
			string strmta;
			strmta = getmta(*it);
			if (!chemta.count(strmta)) {
				chemta.insert(strmta);
				qmta.push(strmta);
			}
		}
		string context;
		getcontext(context);
		while (!qmta.empty()) {
			string sender = getmta(vusr[0]);
			string receiver = qmta.front();
			qmta.pop();
			cout << "Connection between " << sender << " and " << receiver << endl;
			cout << "     HELO " << sender << endl;
			cout << "     250\n";
			cout << "     MAIL FROM:<" << vusr[0] << ">\n";
			cout << "     250\n";
			bool ismta = false;
			for (int i = 1; i < vusr.size(); i++) {
				if (getmta(vusr[i]) == receiver) {
					cout << "     RCPT TO:<" << vusr[i] << ">\n";
					if (smta.count(vusr[i])) {
						cout << "     250\n";
						ismta = true;
					}
					else
						cout << "     550\n";
				}
			}
			if (ismta) {
				cout << "     DATA\n     354\n";
				cout << context;
				cout << "     .\n     250\n";
			}
			cout << "     QUIT\n     221\n";
		}
		susr.clear();
		vusr.resize(0);
		chemta.clear();
	}
	return 0;
}

void getcontext(string& context) {
	string str;
	for (;;) {
		getline(cin, str);
		if (str[0] == '*') break;
		context += "     " + str + "\n";
	}
}

string getmta(string str) {
	int pos = str.find('@');
	return str.substr(pos+1);
}

void usrin(vector<string>& vusr, string& str, set<string>& susr) {
	bool sender = true;
	string strsender;
	for (;;) {
		istringstream ss(str);
		string email;
		while (ss >> email) {
			if (sender) {strsender = email; sender = false;}
			if ((email == strsender)&&(susr.size() > 0))
				vusr.push_back(email);
			if (!susr.count(email)) {
				susr.insert(email);
				vusr.push_back(email);
			}
		}
		getline(cin, str);
		if (str[0] == '*') break;
	}
}

void mtain(set<string>& smta) {
	string mta, str;
	int num;
	for (;;) {
		getline(cin, str);
		if (str[0] == '*') break;
		istringstream ss(str);
		ss >> mta  >>mta >> num;
		string name;
		while (num--) {
			ss >> name;
			smta.insert(name + "@" + mta);
		}
	}
}
