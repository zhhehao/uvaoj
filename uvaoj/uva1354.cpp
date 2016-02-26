#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int maxn = 6;
struct Tree { // 结构树，存储左右树的长度，如果是节点，则左右树的长度都是0,
	double L, R;
	Tree(): L(0), R(0) {}
};

int n, vis[1<<maxn]; // 砝码数目，vis数组记录是否访问过，1<<maxn 表示一个满二叉树的节点数
double r, w[maxn], sum[1<<maxn]; // sum存储每一子集的砝码重量和
vector<Tree> tree[1<<maxn];

void dfs(int subset) {
	if (vis[subset]) return; // 检查是否已经访问过子集
	vis[subset] = true;
	
	bool have_children = false; // 检查是否叶节点
	for (int left = (subset-1)&subset; left; left = (left-1)&subset) {
		have_children = true;

		int right = subset^left; //右树子集，是左树子集与全集异或，即左树补集
		double d1 = sum[right] / sum[subset]; //左天平长度
		double d2 = sum[left] / sum[subset]; // 右天平长度

		dfs(left); dfs(right); // 用二进制遍历的好处

		for (int i = 0; i < tree[left].size(); i++)
			for (int j = 0; j < tree[right].size(); j++) {
				Tree t;
				t.L = max(tree[left][i].L+d1, tree[right][j].L-d2);
				t.R = max(tree[right][j].R+d2, tree[left][i].R-d1);
				if (t.L+t.R < r) tree[subset].push_back(t);
			}
	}

	if (!have_children) tree[subset].push_back(Tree()); // 叶节点的杆长度为0, 加入一个空tree即可
}

int main() {
	int T; scanf("%d", &T) == 1;
	while (T--) {
		scanf("%lf%d", &r, &n) == 2;
		for (int i = 0; i < n; i++) scanf("%lf", &w[i]) == 1; // 浮点运算，一定要都先定义类型
		for (int i = 0; i < (1<<n); i++) {// 遍历所有子集，计算每种子集的砝码重量和
			sum[i] = 0;
			tree[i].clear(); // 顺便清vector
			for (int j = 0; j < n; j++)  // 遍历集合每一个元素，与编码相应的，计算重量和
				if (i & (1<<j)) sum[i] += w[j]; // 把子集重量打表，免去递归时的重复计算
		}

		int root = (1<<n) - 1; // 根节点
		memset(vis, 0, sizeof(vis)); // 使用前，初始化
		dfs(root);
		
		double ans = -1;
		for (int i = 0; i < tree[root].size(); i++) 
			ans = max(ans, tree[root][i].L+tree[root][i].R);// 不用加载algorithm也能用
		printf("%.10lf\n", ans);
	}
	return 0;
}
