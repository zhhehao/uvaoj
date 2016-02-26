#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <algorithm>
#include <cctype>
using namespace std;

#define OUTPUT string& s, map<string, vector<Bucket> >& m

const int maxn = 100 + 5;
vector<string> vpage[maxn]; // 保存所有的文章

struct Bucket {
	int page, line;
};

void rpage(vector<string>& v);
void rcmd(vector<string>& v);
void gcmd(string& str, set<string>& s);
void gbucket( vector<string>& v, const int& n, map<string, vector<Bucket> >& m, set<string>& s);
string getstr(string& s);
void outand(OUTPUT, const int& n);
void outor(OUTPUT, const int& n);
void outnot(OUTPUT, const int& n);
void outterm(OUTPUT);

int main() {
	int n;
	cin >> n;
	string str;
	getline(cin, str); // 除掉一个多余的回车符
	for (int i = 0; i < n; i++) 
		rpage(vpage[i]);
	int m;
	cin >> m;
	getline(cin, str); // 除掉一个多余的回车符
	vector<string> vcmd; // 保存所有的命令行
	set<string> scmd; // 保存所有的关键字
	for (int i = 0; i < m; i++) {
		rcmd(vcmd); // 读入命令行
		gcmd(vcmd[i], scmd); // 从命令行中，读取关键字
	}
	map<string, vector<Bucket> > mbucket; // 存储所有的反向索引
	for (int i = 0; i < n; i++) {
		gbucket(vpage[i], i, mbucket, scmd);	 // 生成反向索引
	}
	for (int i = 0; i < m; i++) {
		if (vcmd[i].find("AND") != -1)
			outand(vcmd[i], mbucket, n);
		else if (vcmd[i].find("OR") != -1)
			outor(vcmd[i], mbucket, n);
		else if (vcmd[i].find("NOT") != -1)
			outnot(vcmd[i], mbucket, n);
		else
			outterm(vcmd[i], mbucket);
	}


	return 0;
}

void outand(OUTPUT, const int& n) {
	stringstream ss(s);
	string w1, w2;
	ss >> w1 >> w2 >> w2;
	if (!m.count(w1) || !m.count(w2)) { // 如果有一个不存在，就输出没有结果
		cout << "Sorry, I found nothing.\n==========\n";
	}
	else {
		set<int> wp1, wp2, wline;
		for (int i = 0; i < m[w1].size(); i++) { // 把包含所有关键字1的文章编号，放入set
			if (!wp1.count(m[w1][i].page))
				wp1.insert(m[w1][i].page);
		}
		for (int i = 0; i < m[w2].size(); i++) { // 同上
			if (!wp2.count(m[w2][i].page))
				wp2.insert(m[w2][i].page);
		}
		bool notfound = true; // 标记是否找到匹配
		vector<int> vp; // 用来放入包含两个关键字的文章编号。
		for (int i = 0; i < n; i++) {
			if (wp1.count(i) && wp2.count(i))
				vp.push_back(i);
		}
		if (vp.size() > 0) // 看有没有匹配
			notfound = false;
		for (int i = 0; i < vp.size(); i++) {
			wline.clear(); // 把匹配文章中，匹配的行号放入set
			for (int j = 0; j < m[w1].size(); j++) {
				if (m[w1][j].page == vp[i]) {
					if (!wline.count(m[w1][j].line))
						wline.insert(m[w1][j].line);
				}
			}
			for (int j = 0; j < m[w2].size(); j++) {
				if (m[w2][j].page == vp[i]) {
					if (!wline.count(m[w2][j].line))
						wline.insert(m[w2][j].line);
				}
			}
			for (set<int>::iterator it = wline.begin(); it != wline.end(); ++it) {
				cout << vpage[vp[i]][*it] << endl;
			}
			if (i < vp.size()-1)
				cout << "----------\n";
		}
		if (notfound) 
			cout << "Sorry, I found nothing.\n";
		cout << "==========\n";
		wp1.clear();
		wp2.clear();
		vp.resize(0);
	}
}

void outor(OUTPUT, const int& n) {
	stringstream ss(s);
	string w1, w2;
	ss >> w1 >> w2 >> w2;
	if (!m.count(w1) && !m.count(w2)) { // 两个关键字都没有，才输出找不到
		cout << "Sorry, I found nothing.\n==========\n";
	}
	else {
		set<int> wp1, wp2, wline;
		if (m.count(w1)) {
			for (int i = 0; i < m[w1].size(); i++) {
				if (!wp1.count(m[w1][i].page))
					wp1.insert(m[w1][i].page);
			}
		}
		if (m.count(w2)) {
			for (int i = 0; i < m[w2].size(); i++) {
				if (!wp2.count(m[w2][i].page))
					wp2.insert(m[w2][i].page);
			}
		}
		bool notfound = true;
		vector<int> vp; // 输入包含1或2的文章编号
		for (int i = 0; i < n; i++) {
			if (wp1.count(i) || wp2.count(i))
				vp.push_back(i);
		}
		if (vp.size() > 0)
			notfound = false;
		for (int i = 0; i < vp.size(); i++) {
			wline.clear(); // 如果关键字在文章里，输入行号
			if (m.count(w1)) {
				for (int j = 0; j < m[w1].size(); j++) {
					if (m[w1][j].page == vp[i]) {
						if (!wline.count(m[w1][j].line))
							wline.insert(m[w1][j].line);
					}
				}
			}
			if (m.count(w2)) {
				for (int j = 0; j < m[w2].size(); j++) {
					if (m[w2][j].page == vp[i]) {
						if (!wline.count(m[w2][j].line))
							wline.insert(m[w2][j].line);
					}
				}
			}
			for (set<int>::iterator it = wline.begin(); it != wline.end(); ++it) {
				cout << vpage[vp[i]][*it] << endl;
			}
			if (i < vp.size()-1)
				cout << "----------\n";
		}
		if (notfound) 
			cout << "Sorry, I found nothing.\n";
		cout << "==========\n";
		wp1.clear();
		wp2.clear();
		vp.resize(0);
	}
}

void outnot(OUTPUT, const int& n) {
	stringstream ss(s);
	ss >> s >> s;
	if (!m.count(s)) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < vpage[i].size(); j++) {
				cout << vpage[i][j] << endl;
			}
			if (i != n - 1)
				cout << "----------\n";
		}
		cout << "==========\n";
	}
	else {
		set<int> sp;
		for (int i = 0; i < m[s].size(); i++) { // 把包含字符串的文章编号，放进一个set
			if (!sp.count(m[s][i].page))
				sp.insert(m[s][i].page);
		}
		if (sp.size() == n) { // 所有文章都有关键字
			cout << "Sorry, I found nothing.\n==========\n";
			sp.clear();
		}
		else {
			int count = n - sp.size() - 1; // 用来标记是否输出要结束了
			for (int i = 0; i < n; i++) {
				if (!sp.count(i)) { // 输出所有不包含关键字的文章
					for (int j = 0; j < vpage[i].size(); j++) {
						cout << vpage[i][j] << endl;
					}
					if (count-- > 0)
						cout << "----------\n";
				}
			}
			cout << "==========\n";
			sp.clear();
		}
	}
}

void outterm(OUTPUT) { 
	if (!m.count(s))
		cout << "Sorry, I found nothing.\n==========\n";
	else {
		set<int> sp;
		for (int i = 0; i < m[s].size(); i++) {
			if (!sp.count(m[s][i].page))
					sp.insert(m[s][i].page);
		}
		int count = sp.size() - 1;
		for (set<int>::iterator it = sp.begin(); it != sp.end(); ++it) {
			for (int i = 0; i < m[s].size(); i++) {
				if (m[s][i].page == *it) {
					cout << vpage[m[s][i].page][m[s][i].line] << endl;
				}
			}
			if (count-- > 0)
				cout << "----------\n";
		}
		cout << "==========\n";
		sp.clear();
	}
}

string getstr(string& s) {
	string str = s;
	for (int i = 0; i < str.size(); i++) {
		if (!isalpha(str[i]))
			str[i] = ' ';
	}
	return str;
}

void gbucket(vector<string>& v, const int& n, map<string, vector<Bucket> >& m, set<string>& s) {
	vector<Bucket> vb;
	Bucket bucket;
	for (int i = 0; i < v.size(); i++) {
		string str = v[i];
		str = getstr(str); // 把所有非字母字符，都变成空格
		stringstream ss(str);
		string words;
		int num = i;
		while (ss >> words) {
			bool isword = true;
			if (isword) {
				transform(words.begin(), words.end(), words.begin(), ::tolower);// 转换成小写
				if (s.count(words)) {
					bucket.page = n;
					bucket.line = num;
					if (m.count(words)) {
						bool nosame = true;
						for (int i = 0; i < m[words].size(); i++) { // 去除重复的记录
							if (m[words][i].page == bucket.page && 
								m[words][i].line == bucket.line) {
								nosame = false;
								break;
							}
						}
						if (nosame)
							m[words].push_back(bucket);
					}
					else {
						vb.resize(0);
						vb.push_back(bucket);
						m[words] = vb;
					}
				}
			}
			else
				continue;
		}
	}
}

void gcmd(string& str, set<string>& s) {
	stringstream ss(str);
	string term;
	while (ss >> term) {
		if (term == "AND" || term == "OR" || term == "NOT")
			continue;
		if (!s.count(term))
			s.insert(term);
	}
}

void rcmd(vector<string>& v) {
	string str;
	while (getline(cin, str) && str.size() == 0)
		;
	v.push_back(str);
}

void rpage(vector<string>& v) {
	string str;
	while (getline(cin, str) && str != "**********")
		v.push_back(str);
}
