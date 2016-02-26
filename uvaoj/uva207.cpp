#include <iostream>
#include <cstdio>
#include <iomanip>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

const double EPS = 1e-8; 

struct Player { 
//	char name[21];
	string sname;
	int rd[4];
	bool isama;
	int total;
	int pi;
	double money;
	bool istie;
};

int inplayer(vector<Player>& v); //get legal player
int rscore(void); // check score
int str2num(const string &s);
bool cmp1(Player a, Player b);
bool cmp2(Player a, Player b);
bool cmp3(Player a, Player b);
bool cmp5(Player a, Player b);

int main() {
	int n; // input case number
	cin >> n;
	while (n--) {
		double purse;
		cin >> purse; // input total purse
		double percent[200];
		memset(percent, 0.0, sizeof(percent));
		for (int i = 0; i < 70; i++)
			cin >> percent[i]; // money percent 
		int pnum;
		cin >> pnum;
		vector<Player> v; // for players who make the first cut.
		string sin;
		getline(cin, sin);
		for (int i = 0; i < pnum; i++)
			inplayer(v); // input all players
		int len = v.size();
		sort(v.begin(), v.end(), cmp1); // 1,2 round score, sort
		for (int i = 70; i < len; i++) // check if tie for 70th score.
			if ((v[69].rd[0]+v[69].rd[1])!=(v[i].rd[0]+v[i].rd[1])) {
				len = i; 
				break;
			}
		v.resize(len); // make the first cut
		sort(v.begin(), v.end(), cmp2); // sort by total score.
		int mcount; // init place 1 player
		if (v[0].isama) {
			v[0].pi = 1;
			v[0].money = -1.0;
			mcount = 0;
		}else{
			v[0].pi = 1;
			v[0].money = percent[0];
			mcount = 1;
		}
		for (int i = 1; i < len;) { // check all players
			if (v[i].total == 10000) { // DQ players 
				for (int k = i; k < len; k++) {
					v[k].pi = 10000;
				}
				break;
			}
			int tie = 0;
			while (v[i+tie].total == v[i-1+tie].total) { //check tie
				tie++;
				if (i-1+tie  == len - 1) break; // avoid cross bundary.
			}
			if (tie == 0) { // no tie player
				v[i].pi = i + 1;
				if (v[i].isama) // check amateur
					v[i].money = -1;
				else {
					if (mcount < 70) { 
						v[i].money = percent[mcount]; // have money
						mcount++;
									
					}else
						v[i].money = -1; // no money
				}
				i++;
				continue;
			}
			if (tie > 0) { // tie player
				int start = i - 1;// 1st tie player
				int end = i - 1 + tie; // last tie player
				int noama = 0; // check amateur
				for (int j = start; j <= end; j++) {
					v[j].pi = v[start].pi;
					if (!v[j].isama) noama++;
				}
				if (noama > 1) 
					for (int j = start; j <= end; j++) 
						if (!v[j].isama) v[j].istie = true;
				if (noama > 0) {	
					double tmoney = 0.0;
					int check;
					if (v[start].isama)
						check = 0;
					else
						check = 1;
					if (mcount - check < 70) {
						for (int p = 0; p < noama; p++) 
							tmoney += percent[mcount+p-check];
						mcount = mcount - check + noama; // next money value 
					}
					else
						tmoney = -1;
					tmoney /= noama;
					for (int j = start; j <= end; j++) 
						if (!v[j].isama)
							v[j].money = tmoney;
//					mcount = mcount - check + noama;
				} else {
					for (int j = start; j <= end; j++)
						v[j].money = -1;
				}
				
				sort(v.begin()+start, v.begin()+end+1, cmp3); // sort tie player (include ama)
				i += tie;
				continue;
			}
		}
		int dqlen = 10000; // sort DQ player.
		for (int i = 0; i < len; i++)
			if (v[i].pi == 10000) {dqlen = i; break;}
		if (dqlen < 10000) {
			sort(v.begin()+dqlen, v.end(), cmp5);
		}
		cout << "Player Name          " << "Place     " // output title 
		<< "RD1  RD2  RD3  RD4  " << "TOTAL     "
		<< "Money Won" << endl;
		for (int i = 0; i < 71; i++) // output second line.
			cout << '-';
		cout << endl;
		for (int i = 0; i < len; i++) {// output players
			cout << v[i].sname << " "; // output player name
			if (v[i].total == 10000)  // dq player no place.
				cout << "          " ;
			if (v[i].pi < 10000) { // output place
				cout << v[i].pi;
				if ((v[i].istie)&&(!v[i].isama)&&(v[i].money>=0)) { // output tie mark
					if (v[i].pi < 10)
						cout << 'T' << "        ";
					else
						cout << 'T' << "       ";
				}
				else { 
					if (v[i].pi < 10)
						cout << "         ";
					else
						cout << "        ";
				}
			}
			cout << left << setw(5) << v[i].rd[0]; // output 1st, 2nd round score
			cout << left << setw(5) << v[i].rd[1];
			if (v[i].rd[2] < 10000)
				cout << left << setw(5) << v[i].rd[2]; // 3rd
			else
				cout << "     ";
			if (v[i].rd[3] < 10000)
				cout << left << setw(5) << v[i].rd[3]; // 4th
			else
				cout << "     ";
			if (v[i].total < 10000) { // output total score
				if ((v[i].isama) || (v[i].money < 0)) { // ama and no money player
					cout << left << setw(3) << v[i].total << endl;
					continue;
				}
				else
					cout << left << setw(10) << v[i].total;
			}
			else {
				cout << left <<  "DQ" << endl; // DQ player
				continue;
			}
			
			if ((v[i].total < 10000)&&(v[i].money >= 0)) { // output money
					cout << '$';
					printf("%9.2f", v[i].money * purse / 100.0 + EPS);
			}
			cout << endl;
		}	

		if (n > 0) // blank line between cases.
			cout << endl;
	}
	return 0;
}

bool cmp1(Player a, Player b) { // 1st, 2nd rounds sort
	if (a.rd[0]+a.rd[1] == b.rd[0]+b.rd[1])
		return a.sname < b.sname;
	return (a.rd[0]+a.rd[1]) < (b.rd[0]+b.rd[1]);
}

bool cmp2(Player a, Player b) {
	return a.total < b.total;
}

bool cmp3(Player a, Player b) {
	return a.sname < b.sname;
}

bool cmp5(Player a, Player b) { // compare function for DQ player
	if ((a.rd[0]+a.rd[1]+a.rd[2]) == (b.rd[0]+b.rd[1]+b.rd[2]))
		return a.sname < b.sname;
	return (a.rd[0]+a.rd[1]+a.rd[2]) < (b.rd[0]+b.rd[1]+b.rd[2]);
}


int inplayer(vector<Player>& v) {
	char c;
	Player player;
//	memset(player.name, '\0', sizeof(player.name));
//	while ((c=getchar()) == '\n')
		;
//	player.name[0] = c; // name done.
	player.isama = false; 
	string sin;
	getline(cin, sin);
	player.sname = sin.substr(0, 20);
	for (int i = 1; i < 20; i++) {
//		player.name[i] = getchar();
		if (player.sname[i] == '*')
			player.isama = true; // amateur check done.
	}
//	player.name[20] = '\0';	// end of name string, remember this line, 
							//	if a long name of 20 char, may be caused wrong output!!!
	player.total = 1; //init player.
	player.rd[0] = 0;
	player.rd[1] = 0;
	player.rd[2] = 0;
	player.rd[3] = 0;
	sin = sin.substr(20, sin.size());
	istringstream ss(sin);
	string str;
	for (int i = 0; i < 2; i++) {
		ss >> str;
		if (str == "DQ"){
			player.total = 0;
			break;
		}else
			player.rd[i] = str2num(str);
	}
	if (player.total == 0) return 1; // can't make the first cut, eliminated.
	ss >> str; 
	if (str == "DQ") { // DQ at 3th round.
		player.rd[2] = 10000;
		player.rd[3] = 10000;
		player.total = 10000;
		goto end;
	}
	player.rd[2] = str2num(str);
	ss >> str;
	if (str == "DQ") {// if DQ, total is 0;
		player.rd[3] = 10000;
		player.total = 10000;
		goto end;
	}
	player.rd[3] = str2num(str);
		player.total = player.rd[0]+player.rd[1]+player.rd[2]+player.rd[3];
	end:
	player.istie = false;
	player.money = -1.0;
	player.pi = 10000;
//	string sname(&player.name[0], &player.name[20]);
//	player.sname = sname;
	v.push_back(player);
}

int rscore(void) { // get round score for players
	char rc[3];
	int score;
	for (int i = 0; i < 3; i++)
		rc[i] = getchar();
		if (rc[1] == 'D') // check DQ
			return 10000;
	sscanf(rc, "%d", &score); // trans string to integer
	return score;
}

int str2num(const string &s) {
	int d = 0;
	for (int i = 0; i != s.size(); i++)
		d = d * 10 + (s[i] - '0');
	return d;
}
