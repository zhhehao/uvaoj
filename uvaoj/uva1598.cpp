#include <iostream>
#include <queue>
#include <string>
#include <sstream>
#include <vector>
#include <cstdio>
using namespace std;

struct Buy {
	int pos, price, sn;
	bool operator < (const Buy &a) const {
		if (price == a.price) 
			return sn > a.sn;
		else
			return price < a.price; // 价格高者优先
	}
};

struct Sell {
	int pos, price, sn;
	bool operator < (const Sell &a) const {
		if (price == a.price)
			return sn > a.sn;
		else
			return price > a.price; // 价格低者优先
	}
};

struct Order {
	int sn, price, quan;
	bool isactive;
	char type;
};

void cancel(int& n, vector<Order>& v, int& bq, int& bp, int& sq, int& sp, priority_queue<Buy>& b, priority_queue<Sell>& s); 
void trade(priority_queue<Buy>& b, priority_queue<Sell>& s, vector<Order>& v, int& bq, int& bp, int& sq, int& sp, string& cmd);
void getquote(int& bq, int& bp, int& sq, int& sp, priority_queue<Buy>& b, priority_queue<Sell>& s, vector<Order>& v) ;
bool clearbuy(priority_queue<Buy>& b, vector<Order>& v);
bool clearsell(priority_queue<Sell>& s, vector<Order>& v);
void getbq(int& bq, int& bp, priority_queue<Buy>& b, vector<Order>& v);
void getsq(int& sq, int& sp, priority_queue<Sell>& s, vector<Order>& v);

int main() {
	string strline;
	int kase = 1;
	while (getline(cin, strline)) {
		stringstream ss(strline);
		int t;
		ss >> t;
		priority_queue<Buy> buyer;
		priority_queue<Sell> seller;
		vector<Order> vorder;
		int bq, bp, sq, sp;
		bq = bp = 0;
		sq = 0;
		sp = 99999;
		if (kase++ > 1)
			cout << endl;
		for (int i = 0; i < t; i++) {
			getline(cin, strline);
			stringstream ss(strline);
			string cmd;
			ss >> cmd;
			if (cmd[0] == 'B') {
				Order order;
				ss >> order.quan >> order.price;
				if (order.price > bp) {
					bp = order.price;
					bq = order.quan;
				}
				else if (order.price == bp)
					bq += order.quan;
				order.sn = i + 1;
				order.isactive = true;
				order.type = 'B';
				vorder.push_back(order);
				Buy buy;
				buy.price = order.price;
				buy.pos = vorder.size() - 1;
				buy.sn = i + 1;
				buyer.push(buy);
			}
			else if (cmd[0] == 'S') {
				Order order;
				ss >> order.quan >> order.price;
				if (order.price < sp) {
					sp = order.price;
					sq = order.quan;
				}
				else if (order.price == sp)
					sq += order.quan;
				order.sn = i + 1;
				order.isactive = true;
				order.type = 'S';
				vorder.push_back(order);
				Sell sell;
				sell.price = order.price;
				sell.pos = vorder.size() - 1;
				sell.sn = i + 1;
				seller.push(sell);
			}
			else {
				int sn;
				ss >> sn;
				cancel(sn, vorder, bq, bp, sq, sp, buyer, seller);
			}
			trade(buyer, seller, vorder, bq, bp, sq, sp, cmd);
//			getquote(bq, bp, sq, sp, buyer, seller, vorder);
			printf("QUOTE %d %d - %d %d\n", bq, bp, sq, sp);		
		}
		vorder.resize(0);
		getline(cin, strline);
	}
	return 0;
}

void trade(priority_queue<Buy>& b, priority_queue<Sell>& s, vector<Order>& v, int& bq, int& bp, int& sq, int& sp, string& cmd) {
	bool change = false;
	begin:
	if (clearbuy(b, v) && clearsell(s, v)) {
		if (b.top().price >= s.top().price) {	
			if (cmd[0] == 'B') {
				int tprice = s.top().price;	
				if (v[b.top().pos].quan == v[s.top().pos].quan) {
					int tquan = v[b.top().pos].quan;
					v[b.top().pos].isactive = false;
					v[s.top().pos].isactive = false;
					b.pop();
					s.pop();
					printf("TRADE %d %d\n", tquan, tprice);
					change = true;
					goto end;
				}
				if (v[b.top().pos].quan < v[s.top().pos].quan) {
					int tquan = v[b.top().pos].quan;
					v[b.top().pos].isactive = false;
					b.pop();
					v[s.top().pos].quan -= tquan;
					printf("TRADE %d %d\n", tquan, tprice);
					change = true;
					goto end;
				}
				if (v[b.top().pos].quan > v[s.top().pos].quan) {
					int tquan = v[s.top().pos].quan;
					v[s.top().pos].isactive = false;
					s.pop();
					v[b.top().pos].quan -= tquan;
					printf("TRADE %d %d\n", tquan, tprice);
					change = true;
					goto begin;
				}
			}
			else {
				int tprice = b.top().price;
				if (v[b.top().pos].quan == v[s.top().pos].quan) {
					int tquan = v[b.top().pos].quan;
					v[b.top().pos].isactive = false;
					v[s.top().pos].isactive = false;
					b.pop();
					s.pop();
					printf("TRADE %d %d\n", tquan, tprice);
					change = true;
					goto end;
				}
				if (v[b.top().pos].quan < v[s.top().pos].quan) {
					int tquan = v[b.top().pos].quan;
					v[b.top().pos].isactive = false;
					b.pop();
					v[s.top().pos].quan -= tquan;
					printf("TRADE %d %d\n", tquan, tprice);
					change = true;
					goto begin;
				}
				if (v[b.top().pos].quan > v[s.top().pos].quan) {
					int tquan = v[s.top().pos].quan;
					v[s.top().pos].isactive = false;
					s.pop();
					v[b.top().pos].quan -= tquan;
					printf("TRADE %d %d\n", tquan, tprice);
					change = true;
					goto end;
				}
			}
		}
	}
	end:
	if (change)
		getquote(bq, bp, sq, sp, b, s, v);
}

void getbq(int& bq, int& bp, priority_queue<Buy>& b, vector<Order>& v) {
	int maxprice = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i].price > maxprice && v[i].isactive && v[i].type == 'B')
			maxprice = v[i].price;
	}
	bp = maxprice;
	bq = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i].price == maxprice && v[i].isactive && v[i].type == 'B')
			bq += v[i].quan;
	}
}

void getsq(int& sq, int& sp, priority_queue<Sell>& s, vector<Order>& v) {
	int minprice = 99999;
	for (int i = 0; i < v.size(); i++) {
		if (v[i].price < minprice && v[i].isactive && v[i].type == 'S')
			minprice = v[i].price;
	}
	sp = minprice;
	sq = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i].price == minprice && v[i].isactive && v[i].type == 'S')
			sq += v[i].quan;
	}
}

void getquote(int& bq, int& bp, int& sq, int& sp, priority_queue<Buy>& b, priority_queue<Sell>& s, vector<Order>& v) {
	if (clearbuy(b, v)) {
		getbq(bq, bp, b, v);
	}
	else {
		bq = bp = 0;	
	}
	if (clearsell(s, v)) {
		getsq(sq, sp, s, v);
	}
	else {
		sq = 0;
		sp = 99999;
	}
}

bool clearbuy(priority_queue<Buy>& b, vector<Order>& v) {
	if (!b.empty()) {
		while (!v[b.top().pos].isactive) {
			b.pop();
			if (b.empty())
				break;
		}
	}
	if (!b.empty()) 
		return true;
	else
		return false;
}

bool clearsell(priority_queue<Sell>& s, vector<Order>& v) {
	if (!s.empty()) {
		while (!v[s.top().pos].isactive) {
			s.pop();
			if (s.empty())
				break;
		}
	}
	if (!s.empty())
		return true;
	else 
		return false;
}

void cancel(int& n, vector<Order>& v, int& bq, int& bp, int& sq, int& sp, priority_queue<Buy>& b, priority_queue<Sell>& s) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i].sn == n) {
			if (v[i].isactive) {
				v[i].isactive = false;
				if (v[i].price == bp && v[i].quan > 0 && v[i].type == 'B') {
					bq -= v[i].quan;
					if (bq == 0)
						getquote(bq, bp, sq, sp, b, s, v);
				}
				if (v[i].price == sp && v[i].quan > 0 && v[i].type == 'S') {
					sq -= v[i].quan;
					if (sq == 0)
						getquote(bq, bp, sq, sp, b, s, v);
				}
				break;
			}
			else
				break;
		}
	}
}
