#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

struct Book {
	string title, author;
};

void stockin(vector<Book>& v);
bool cmp (const Book& a, const Book& b);
void borrow(vector<Book>& v, const string& s, map<string, int>& m);
void retu(vector<Book>& vs, vector<Book>& vr, const string& s, map<string, int>& m);
void shelve(vector<Book>& vs, vector<Book>& vr, map<string, int>& m);

int main() {
	vector<Book> vs;
	vector<Book> vr;
	map<string, int> ms;
	stockin(vs);
	sort(vs.begin(), vs.end(), cmp);
	for (int i = 0; i < vs.size(); i++) // storage title and position into map
		ms[vs[i].title] = i;
	string command;
	while (getline(cin, command) && command != "END") {
		if (command[0] == 'B') {
			borrow(vs, command, ms);
			continue;
		}
		if (command[0] == 'R') {
			retu(vs, vr, command, ms);
			continue;
		}
		if (command == "SHELVE") {
			shelve(vs, vr, ms);
		}
	}
	return 0;
}

void borrow(vector<Book>& v, const string& s, map<string, int>& m) {
	string title;
	title = s.substr(7, s.size()-7);
	v[m[title]].title = "";
}

void retu(vector<Book>&vs, vector<Book>& vr, const string& s, map<string, int>& m) {
	string title;
	title = s.substr(7, s.size()-7);
	Book book;
	book.title = title;
	book.author = vs[m[title]].author;
	vr.push_back(book);
}

void shelve(vector<Book>& vs, vector<Book>& vr, map<string, int>&m) {
	sort(vr.begin(), vr.end(), cmp);
	for (int i = 0; i < vr.size(); i++) {
		int pos = m[vr[i].title];
		if (pos == 0) {
			vs[0].title = vr[i].title;
			cout << "Put " << vr[i].title << " first\n";
			continue;
		}
		vs[pos].title = vr[i].title;
		string title;
		bool first = true;
		for (int j = pos - 1; j >= 0; j--) {
			if (vs[j].title != "") {
				cout << "Put " << vr[i].title << " after " << vs[j].title << endl;
				first = false;
				break;
			}
		}
		if (first)
			cout << "Put " << vr[i].title << " first\n";
	}
	cout << "END\n";
	vr.resize(0);
}

bool cmp (const Book& a, const Book& b) {
	if (a.author == b.author)
		return a.title < b.title;
	else
		return a.author < b.author;
}

void stockin(vector<Book>& v) {
	string str;
	Book book;
	while (getline(cin, str) && str != "END") {
		book.title = str.substr(0, str.find('\"', 1)+1);
		book.author = str.substr(str.find('\"', 1) + 5);
		v.push_back(book);
	}
}
